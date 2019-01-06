#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "graphreader.h"
#include "graph.h"
#include "webserver.h"
//#include "searchthread.h"

Graph graph;

/**
 * Dijkstra routing to all  
 */
int routeToAll(){
    std::cout << "routeToAll" << std::endl;
    return 0;
}

int routeToOne(){
    std::cout << "routeToOne" << std::endl;
    return 0;
}

int defaultSearch(){
    std::cout << "defaultSearch" << std::endl;
    return 0;
}

int runWebserver()
{
  std::cout << "starting the Webserver" << std::endl;
  Webserver::run_server();
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
      std::cout << "---------Graph imported--------" << std::endl;
      std::cout << "Edges: " << graph.edgecount << std::endl;
      std::cout << "Nodes: " << graph.nodecount << std::endl;
      std::cout << "-------------------------------" << std::endl;
      
      
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
          default: std::cout<<"Please select one of the Options in the List"<<std::endl;
            break;
      }
    }
  }
  return 0;

}