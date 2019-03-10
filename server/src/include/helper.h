#ifndef HELPER_H
#define HELPER_H

#include "edge.h"
#include "graph.h"
#include <cmath>
#include <stdio.h>
#include <math.h>


extern Graph graph;

struct sort_operator
{
  inline bool operator() (const Edge& edge1, const Edge& edge2)
  {
    return (edge1.srcID < edge2.srcID);
  }
};

/**
 * sort two pairs by checking the first entry
*/
struct pair_sort_operator
{
  inline bool operator() (const pair<int,int>& firstPair, const pair<int,int> secondPair)
  {
    return (get<0>(firstPair) > get<0>(secondPair));
  }
};


  /**
   * check float is equal
   */
  static bool double_equals(double a, double b, double epsilon = 0.00001)
  {
    return std::abs(a - b) < epsilon;
  }

  static double point_distance(double x1 , double x2, double y1, double y2){
    return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
  }
  #endif