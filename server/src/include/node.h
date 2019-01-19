#include <cstdint>
#include <map>
#include <string>

using namespace std;

#ifndef NODE_H
#define NODE_H

struct Node
{
  // Node information
  long id;
  float lat;
  float lon;
  int dist;
  
  Node();
  Node(long _nodeid, float _latitude, float _longitude);
  Node(long _nodeid);
};

#endif