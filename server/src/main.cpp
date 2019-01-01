#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
//#include "graphreader.h"
//#include "graph.h"
//#include "searchthread.h"

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


int main(int argc, char *argv[]){
    int operation;
    // current time
    //std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    // if argument exists read file
    if(argc > 1){
    
    /*
    //----------- import File -----------//
    std::cout << "Importing File" << std::endl;
    // load File
    std::ifstream infile(argv[1]);
    // read File and load into Graphstructure
    //Graph graph;
    graphReader::readGraph(infile, &graph);
    // time needed for import
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto durationImport = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "time needed for import: " << durationImport << " microseconds" << std::endl;
    */
    

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
      default: std::cout<<"Please select one of the Options in the List"<<std::endl;
        break;
      }
    }
  }
  return 0;

}