#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"
#include <boost/property_tree/ptree.hpp>

struct Search
{
  static int findNode(Graph *graph, double latitude, double longitude);
  static boost::property_tree::ptree randomWayReturn(Graph *graph, int srcIDX);
};

#endif