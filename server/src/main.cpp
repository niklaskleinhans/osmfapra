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
  std::cout << "[edecount:edgearraysize]    => " << "[" <<graph.edgecount << " : " << graph.edges.size()<< "]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "\n" << std::endl;
  std::cout << "-------Check Edges--------" << std::endl;
  Edge e;
  int sink =0;
  boost::random::mt19937 gen;
  for (int m=0; m< graph.nodecount; ++m)
  {
    if( graph.offset[m] == -1) 
    {
      //std::cout<< "[" << m << ":" << graph.nodes[m].lon << ":" << graph.nodes[m].lat << std::endl;
      sink++;
      continue;
    }
    if(m != graph.edges[graph.offset[m]].srcID){
        std::cout << "EDGES for ID: " << m << " are wrong " << "found Edge for ID: " << graph.edges[graph.offset[m]].srcID  << std::endl;
        std::cout << "Nodeinformation fpr ID: " << "lat: " << graph.nodes[m].lat << " lon: " << graph.nodes[m].lon << std::endl;
        std::cout << "Offset returns for ID: " << m << " : " << graph.offset[m] << std::endl;
    } 
    if(m >= 1 && m-1 != graph.edges[graph.offset[m]].srcID-1)
    {
      std::cout << "previous EDGES for ID: " << m << " are wrong"<< std::endl;
    }
  }
  std::cout << "Sink Point Count: " << sink<< std::endl;
 
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

int main(int argc, char *argv[]){
    int operation;
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
  }
  return 0;

}