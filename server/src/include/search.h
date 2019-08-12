#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"
#include "helper.h"
#include "node.h"
#include <queue>
#include <boost/property_tree/ptree.hpp>

struct Result
{
  int distance = -1;
  int pathCost = 0;
  std::vector<Node> path;
};


struct Search
{
  Graph* graph;
  std::vector<bool> visited;
  std::vector<int> parents;
  std::vector<int> distances;
  std::vector<int> touch_visited;
  std::vector<int> touch_parents;
  std::priority_queue<pair<int,int>, std::vector<pair<int,int>>, pair_sort_operator> priorityQueue;

  static int findNode(Graph *graph, double latitude, double longitude);
  static boost::property_tree::ptree randomWayReturn(Graph *graph, int srcIDX);

  void oneToOne(int source, int target, Result* result);
  void getPath(int source,int currNode, vector<Node>* path);
  void expand(int source, int costs);
  void reset();

  Search(Graph* graph);
};

#endif