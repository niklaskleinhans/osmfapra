#include "webserver.h"
#include "graph.h"
#include "include/search.h"
#include <boost/foreach.hpp>
#include "client_https.hpp"
#include "server_https.hpp"
#include "graph.h"
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <crypto.hpp>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <iomanip>

inline ptree path_to_ptree(vector<Node> path){

  boost::property_tree::ptree matrix_node;
  for (int i = 0; i < path.size(); i++)
    {
      //std::cout << result[i] << " : " << node[0] << " : " << node[1] << std::endl;
      boost::property_tree::ptree row;
      // Create an unnamed value
      boost::property_tree::ptree cell1;
      cell1.put_value(path[i].lat);
      // Add the value to our row
      row.push_back(std::make_pair("", cell1));
      boost::property_tree::ptree cell2;
      cell2.put_value(path[i].lon);
      // Add the value to our row
      row.push_back(std::make_pair("", cell2));


      // Add the row to our matrix
      matrix_node.push_back(std::make_pair("", row));
    }
  return matrix_node;
}

/**
 * Starting the Webserver
 * @Param Graph graph
 */
void Webserver::run_server(Graph *graph){
// HTTP-server at port 8080 using 1 thread
  // Unless you do more heavy non-threaded processing in the resources,
  // 1 thread is usually faster than several threads
  HttpServer server("../../data/example.com.pem", "../../data/example.com-key.pem");
  server.config.port = 8080;
  // Default GET-example. If no other matches, this anonymous function will be called.
  // Will respond with content in the web/-directory, and its subdirectories.
  // Default file: index.html
  // Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server
  server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    try {
      auto web_root_path = boost::filesystem::canonical("../web");
      auto path = boost::filesystem::canonical(web_root_path / request->path);
      // Check if path is within web_root_path
      if(distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
         !equal(web_root_path.begin(), web_root_path.end(), path.begin()))
        throw invalid_argument("path must be within root path");
      if(boost::filesystem::is_directory(path))
        path /= "index.html";

      SimpleWeb::CaseInsensitiveMultimap header;

      // Uncomment the following line to enable Cache-Control
      // header.emplace("Cache-Control", "max-age=86400");


      auto ifs = make_shared<ifstream>();
      ifs->open(path.string(), ifstream::in | ios::binary | ios::ate);

      if(*ifs) {
        auto length = ifs->tellg();
        ifs->seekg(0, ios::beg);

        header.emplace("Content-Length", to_string(length));
        response->write(header);

        // Trick to define a recursive function within this scope (for example purposes)
        class FileServer {
        public:
          static void read_and_send(const shared_ptr<HttpServer::Response> &response, const shared_ptr<ifstream> &ifs) {
            // Read and send 128 KB at a time
            static vector<char> buffer(131072); // Safe when server is running on one thread
            streamsize read_length;
            if((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) > 0) {
              response->write(&buffer[0], read_length);
              if(read_length == static_cast<streamsize>(buffer.size())) {
                response->send([response, ifs](const SimpleWeb::error_code &ec) {
                  if(!ec)
                    read_and_send(response, ifs);
                  else
                    cerr << "Connection interrupted" << endl;
                });
              }
            }
          }
        };
        FileServer::read_and_send(response, ifs);
      }
      else
        throw invalid_argument("could not read file");
    }
    catch(const exception &e) {
      response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": " + e.what());
    }
  };


  // Add route to search by coordinates
  server.resource["^/getserverinfo$"]["GET"] = [&](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    try {
    ptree pt;
    std::ostringstream oss;
    pt.put("nodecount", graph->nodecount);
    pt.put("edgecount", graph->edgecount);
    pt.put("timeForImport", (graph->durationImport + graph->durationSortAndOffset));

    std::cout << "send callback now" << std::endl;

    // TODO VÖLLIGER MIST
    write_json(oss, pt);

    std::string jsonString = oss.str();
    //std::cout << jsonString << std::endl;
    *response 
    << "HTTP/1.1 200 OK\r\n"
    << "Content-Length: " << jsonString.length() << "\r\n\r\n"
    << jsonString;
    }
    catch(const exception &e) {
      *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
                << e.what();
    }
  };


  // Add route to search by coordinates
  server.resource["^/routebycoordinate$"]["POST"] = [&](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    try {
    std::cout << "Post json"<< std::endl;
    ptree pt;
    read_json(request->content, pt);

    std::ostringstream oss;


    string resultJson;
    // std::cout << std::setprecision(16) << pt.get<double>("srcLongitude") << std::endl;
    int srcIDX = Search::findNode(graph, pt.get<double>("srcLongitude"), pt.get<double>("srcLatitude"));
    int trgIDX = Search::findNode(graph, pt.get<double>("trgLongitude"), pt.get<double>("trgLatitude"));
    std::string algorithm = pt.get<std::string>("algorithm");

    Result result;
    if ( srcIDX != -1 && trgIDX !=-1){
      Search search(graph);
      if (algorithm.compare("dijkstra") == 0 ){
        search.oneToOne(srcIDX, trgIDX, &result);
      }else{
        search.oneToOneBidirectional(srcIDX, trgIDX, &result);
      }
    
      pt.add_child("nodes", path_to_ptree(result.path));
      pt.put("pathCost", result.pathCost);
      pt.put("timeForSearch", result.timeForSearch);
      pt.put("error", false);
    } else{
      pt.put("error", true);
      pt.put("errorMessage", "could not find a nodeid");
    }

    std::cout << "send callback now" << std::endl;

    //write_json(std::cout,pt);

    // TODO VÖLLIGER MIST
    write_json(oss, pt);

    std::string jsonString = oss.str();
    //std::cout << jsonString << std::endl;
    *response 
    << "HTTP/1.1 200 OK\r\n"
    << "Content-Length: " << jsonString.length() << "\r\n\r\n"
    << jsonString;
    }
    catch(const exception &e) {
      *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
                << e.what();
    }
  };

  // Add Route for nodeid search
  server.resource["^/routebynodeid$"]["POST"] = [&](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    try {
      std::cout << "Post json"<< std::endl;
      ptree pt;
      read_json(request->content, pt);

      std::ostringstream oss;

      string resultJson;
      int srcIDX = pt.get<int>("srcNode");
      int trgIDX = pt.get<int>("trgNode");

      std::cout << srcIDX << " : " << trgIDX << std::endl;

      pt.add_child("nodes", Search::randomWayReturn(graph,srcIDX));
      std::cout << "send callback now" << std::endl;

      //write_json(std::cout,pt);

      // TODO VÖLLIGER MIST
      write_json(oss, pt);

      std::string jsonString = oss.str();
      //std::cout << jsonString << std::endl;
      *response 
      << "HTTP/1.1 200 OK\r\n"
      << "Content-Length: " << jsonString.length() << "\r\n\r\n"
      << jsonString;
    }
    catch(const exception &e) {
      *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
      << e.what();
    }
  };

  // Add route to search by coordinates
  server.resource["^/generatesharingsession$"]["POST"] = [&](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    try {
      std::string sessionContent = "test";
      std::ostringstream oss;

      std::string jsonString = sessionContent;
      //std::cout << jsonString << std::endl;
      *response 
      << "HTTP/1.1 200 OK\r\n"
      << "Content-Length: " << jsonString.length() << "\r\n\r\n"
      << jsonString;
    }
    catch(const exception &e) {
      *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
                << e.what();
    }
  };

  
  server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
    // Handle errors here
  };

  thread server_thread([&server]() {
    // Start server
      std::cout<<"Started Webserver" << std::endl;
      std::cout<<"Open in your browser: " << "https://localhost" << ":" << server.config.port << std::endl;
    server.start();
  });
  
  server_thread.join();
}