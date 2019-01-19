#ifndef EDGE_H
#define EDGE_H

struct Edge
{
  int srcID;
  int trgID;
  int cost;
  int maxSpeed;
  Edge(int _src, int _trg, int _maxSpeed);
  Edge(int _src, int _trg);
  Edge();
};

#endif