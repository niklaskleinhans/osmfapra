#include "node.h"

Node::Node(long _nodeID, float _latitude, float _longitude)
{
    id = _nodeID;
    lat = _latitude;
    lon = _longitude;
}

Node::Node(long _nodeID)
{
    id= _nodeID;
}
Node::Node(){}