#ifndef GRAPH_H
#define GRAPH_H
#include <cstdint>

#include "node.h"
#include "edge.h"
#include <vector>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct Graph
{
  int nodecount;
  int edgecount;
  long durationImport;
  long durationSortAndOffset;
  
  std::map<std::string,int> highwaystat;
  std::vector<Node> nodes;
  std::vector<Edge> edges;
  std::vector<int> offset;

  int findNode(double longitude, double latitude);
};

#endif// GRAPH_H
