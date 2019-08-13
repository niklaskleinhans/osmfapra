#include <stdio.h>
#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <sstream>
#include <chrono>
#include "graphreader.h"
#include "graph.h"
#include "webserver.h"
#include "edge.h"
#include "include/search.h"

#define BINARYREAD false
#define BINARYWRITE false
#define BINARYFILE "../../data/graphbin"


Graph graph;

/**
 * Print some Stats
 */ 
int printGraphStats()
{

  std::cout << "\n" << std::endl;
  std::cout << "----------Graph-----------" << std::endl;
  std::cout << "Edges: " << graph.edgecount << std::endl;
  std::cout << "Nodes: " << graph.nodecount << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "\n" << std::endl;
  std::cout << "----------Highways--------" << std::endl;
  for (map<std::string, int>::iterator it = graph.highwaystat.begin(); it != graph.highwaystat.end(); it++)
  {
    std::cout << it->first << " : " << it->second << std::endl;
  }
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
  std::cout << "[nodecount:offsetREVERSEDarraysize] => " << "[" <<graph.nodecount << " : " << graph.offsetReversed.size()<< "]" << std::endl;
  std::cout << "[edecount:edgearraysize]    => " << "[" <<graph.edgecount << " : " << graph.edges.size()<< "]" << std::endl;
  std::cout << "[edecount:edgeREVERSEDarraysize]    => " << "[" <<graph.edgecount << " : " << graph.edgesReversed.size()<< "]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "\n" << std::endl;
  std::cout << "-------Check Edges--------" << std::endl;
  Edge e;
  int sink =0;
  int currentEdgeID=0;
  int sumOfMultiEdges = 0;
  boost::random::mt19937 gen;
  std::vector<int> edgeCostValues;
  std::vector<int> maxSpeedValues;
  
  for (int m=0; m< graph.nodecount; ++m)
  {

    currentEdgeID=graph.offset[m];
    edgeCostValues.push_back(graph.edges[currentEdgeID].cost);
    maxSpeedValues.push_back(graph.edges[currentEdgeID].maxSpeed);
    // count nodes with no outgoing edges
    if( currentEdgeID == -1) 
    {
      //std::cout<< "[" << m << ":" << graph.nodes[m].lon << ":" << graph.nodes[m].lat << std::endl;
      sink++;
      continue;
    }
    // check if the returned id off the offset for nodeid m
    // equals a edge entry of the edge array with 
    // srcID = requested nodeid m
    // Just to check if the offset array works fine
    if(m != graph.edges[currentEdgeID].srcID){
        std::cout << "EDGES for ID: " << m << " are wrong " << "found Edge for ID: " << graph.edges[currentEdgeID].srcID  << std::endl;
        std::cout << "Nodeinformation fpr ID: " << "lat: " << graph.nodes[m].lat << " lon: " << graph.nodes[m].lon << std::endl;
        std::cout << "Offset returns for ID: " << m << " : " << graph.offset[m] << std::endl;
    } 
    // check if the edge array is sorted correctly
    if(m >= 1 && m-1 != graph.edges[graph.offset[m]].srcID-1)
    {
      std::cout << "previous EDGES for ID: " << m << " are wrong"<< std::endl;
    }

    // check if all of the edges just exists once
    int edgeIteration = currentEdgeID;
    std::vector<int> existingtargets;
    while(graph.edges[edgeIteration].srcID == graph.edges[currentEdgeID].srcID)
    {
      if(std::find(existingtargets.begin(), existingtargets.end(), graph.edges[edgeIteration].trgID) != existingtargets.end())
      {
        sumOfMultiEdges++;
        //std::cout << "Found Edge again: " << edgeIteration << " : "<< m << " : " << graph.edges[edgeIteration].trgID  << std::endl;
      }else
      {
        existingtargets.push_back(graph.edges[edgeIteration].trgID);
      }
        edgeIteration++;
    }
  }

  std::cout << "Multi Edge Count: " << sumOfMultiEdges << std::endl;
  std::cout << "Sink Point Count: " << sink<< std::endl;
  std::cout << "--------------------------" << std::endl;
  std::sort(maxSpeedValues.begin(), maxSpeedValues.end());
  auto uniquemaxSpeedList = std::unique(maxSpeedValues.begin(), maxSpeedValues.end());
  maxSpeedValues.erase(uniquemaxSpeedList, maxSpeedValues.end());
  std::cout << " maxSpeed List: "  << std::endl;
  for (int i : maxSpeedValues) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  std::cout << "--------------------------" << std::endl;
  return 0;
}

/**
 * starts the Webserver
 */ 
int runWebserver()
{
  std::cout << "starting the Webserver" << std::endl;
  //run_server();
  Webserver::run_server(&graph);
  return 0;
}

/**
 * Reads the graph from binary file
 **/
int readBinary()
{
  fstream file;
  file.open(BINARYFILE, ios::in | ios::binary);
  if(!file)
  {
    std::cout << "error in opening the file" << std::endl;
    return -1;
  }
  
  if(file.read((char*)&graph, sizeof(graph)))
  {
    std::cout << "Data extracted from file"<< std::endl;
  } else
  {
    std::cout<< "Error in reading data from file" << std::endl;
    return -1;
  }
  file.close();
  return 1;
}

/**
 * Write the graph into a binary file
 **/
int writeBinary()
{
  fstream file;
  file.open(BINARYFILE, ios::out|ios::binary);
  if(!file){
    std::cout << "Error in creating file.." << std::endl;
    return -1;
  }

  file.write((char*)&graph,sizeof(graph));
  file.close();
  std::cout<< "Data saved into file" << std::endl;
  return 1;

}

int main(int argc, char *argv[]){
    int operation;
    // if argument exists read file
    if(argc > 1){
  
      //----------- import File -----------//
      // read File and load into Graphstructure
      // Graph graph;
      if(!(BINARYREAD && readBinary())) GraphReader::read(&graph, argv[1]);
      if(BINARYWRITE) writeBinary();
      
      /*
      //--------- User interaction ---------//
      bool exit = false;
      while(!exit){
        std::cout << "\n" << std::endl;
        std::cout << "---------------------" << std::endl;
        std::cout << "Please enter desired operation: " << std::endl;
        std::cout << "(1) start the Webserver" << std::endl;
        std::cout << "(2) Print some Stats " << std::endl;
        std::cout << "(3) Quit" << std::endl;
        std::cin >> operation;

        switch(operation){
          case 3: exit=true;
            break;
          case 1: runWebserver();
            break;
          case 2: printGraphStats();
            break;
          default: std::cout<<"Please select one of the Options in the List"<<std::endl;
            break;
      }
    }
    */
    runWebserver();
  }
  return 0;

}