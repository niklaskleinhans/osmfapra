#include <stdio.h>
#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <fstream>
#include <sstream>
#include <chrono>
#include "graphreader.h"
#include "graph.h"
#include "webserver.h"
#include "edge.h"

Graph graph;

/**
 * Dijkstra routing to all  
 */
int routeToAll(){
    std::cout << "routeToAll" << std::endl;
    return 0;
}

/**
 * Dijkstra routing to target
 */
int routeToOne(){
    std::cout << "routeToOne" << std::endl;
    return 0;
}

/**
 *  Dijstra defined default search
 */ 
int defaultSearch(){
    std::cout << "defaultSearch" << std::endl;
    return 0;
}

/**
 * starts the Webserver
 */ 
int runWebserver()
{
  std::cout << "starting the Webserver" << std::endl;
  Webserver::run_server();
  return 0;
}

int printGraphStats()
{

  std::cout << "\n" << std::endl;
  std::cout << "----------Graph-----------" << std::endl;
  std::cout << "Edges: " << graph.edgecount << std::endl;
  std::cout << "Nodes: " << graph.nodecount << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "\n" << std::endl;
  std::cout << "----------Import----------" << std::endl;
  std::cout << "time needed for import: " << graph.durationImport << " microseconds" << std::endl;
  std::cout << "=> " << (graph.durationImport /(long)1000000) << " seconds" << std::endl;
  std::cout << "=> " << (graph.durationImport /(long)60000000) << " minutes" << std::endl;
  std::cout << "time needed for Sort and Offset: " << graph.durationSortAndOffset << " microseconds" << std::endl;
  std::cout << "=> " << (graph.durationSortAndOffset /(long)1000000) << " seconds" << std::endl;
  std::cout << "=> " << (graph.durationSortAndOffset /(long)60000000) << " minutes" << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "\n" << std::endl;
  std::cout << "------Array Check---------" << std::endl;
  std::cout << "[nodecount:nodearraysiz]    => " << "[" <<graph.nodecount << " : " << graph.nodes.size()<< "]" << std::endl;
  std::cout << "[nodecount:offsetarraysize] => " << "[" <<graph.nodecount << " : " << graph.offset.size()<< "]" << std::endl;
  std::cout << "[edecount:edgearraysize]    => " << "[" <<graph.edgecount << " : " << graph.edges.size()<< "]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "\n" << std::endl;
  std::cout << "-------Check Edges--------" << std::endl;
  Edge e;
  boost::random::mt19937 gen;
  for (int i=0; i<20; i++)
  {
    // random edge
    boost::random::uniform_int_distribution<> dist(1, graph.nodecount); 
    int j = dist(gen);
    // check if edges exists
    if(graph.offset[j] < 0) {
      std::cout << "NO EDGE FOR: [" << j << "] ";
      continue;
    };
    e = Edge(graph.edges[graph.offset[j]]);

    std::cout << "Asked for Nodeinformations: [" << j << "] ";
    std::cout << "=> latitude: " << "[" << graph.nodes[j].lat << "] ";
    std::cout << "=> longitude: " << "[" << graph.nodes[j].lon << "] " << std::endl;
    std::cout << "Asked for an Edge of Node: [" << j << "] ";
    std::cout << "=> offsetvalue : [" << graph.offset[j] << "] ";
    int edgecounter = 0;
    while(e.srcID == graph.edges[graph.offset[j]].srcID)
    {
      j++;
      edgecounter++;
    }
    std::cout << "=> ExampleEdge: [" << e.srcID << " : " << e.trgID << "]";
    std::cout << "=> Edgecount: [" << edgecounter << "]"<< std::endl;

  }
  std::cout << "--------------------------" << std::endl;
  return 0;
}


int main(int argc, char *argv[]){
    int operation;
    // current time
    // if argument exists read file
    if(argc > 1){
    
  
      //----------- import File -----------//
      // read File and load into Graphstructure
      // Graph graph;
    
      GraphReader::read(&graph, argv[1]);
      
      
      //--------- User interaction ---------//
      bool exit = false;
      while(!exit){
        std::cout << "\n" << std::endl;
        std::cout << "---------------------" << std::endl;
        std::cout << "Please enter desired operation: " << std::endl;
        std::cout << "(1) Route to all" << std::endl;
        std::cout << "(2) Route to target " << std::endl;
        std::cout << "(3) Quit" << std::endl;
        std::cout << "(4) default(routeToAll 8371825)" << std::endl;
        std::cout << "(5) starting the webserver" << std::endl;
        std::cout << "(6) check some stats" << std::endl;
        std::cin >> operation;

        switch(operation){
          case 1: routeToAll();
            break;
          case 2: routeToOne();
            break;
          case 3: exit=true;
            break;
          case 4: defaultSearch();
            break;
          case 5: runWebserver();
            break;
          case 6: printGraphStats();
            break;
          default: std::cout<<"Please select one of the Options in the List"<<std::endl;
            break;
      }
    }
  }
  return 0;

}