#include "edge.h"

Edge::Edge(int _srcID, int _trgID, int _maxSpeed)
{
    srcID = _srcID;
    trgID = _trgID;
    maxSpeed = _maxSpeed;
}

Edge::Edge(int _srcID, int _trgID)
{
    srcID = _srcID;
    trgID = _trgID;
}

Edge::Edge(){}