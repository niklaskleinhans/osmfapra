#include "edge.h"

struct sort_operator
{
  inline bool operator() (const Edge& edge1, const Edge& edge2)
  {
    return (edge1.srcID < edge2.srcID);
  }
};