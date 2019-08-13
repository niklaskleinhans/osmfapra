#include <string>
#include "graph.h"
#include <osmpbf/blobfile.h>
#include <osmpbf/osmfile.h>
#include <osmpbf/primitiveblockinputadaptor.h>
#include <osmpbf/inode.h>
#include <osmpbf/iway.h>
#include <osmpbf/irelation.h>

#ifndef GRAPHREADER_H
#define GRAPHREADER_H


struct GraphReader{
  //int read(Graph* out, char * inputFileName, bool verbose, std::map<string, vector<string>> categories);
  static int read(Graph* out, char * inputFileName);
  static int createOffset(Graph* graph);
  static int createOffsetReversed(Graph* graph);
  static int cleanUpMultiEdges(Graph* graph);
        
};

#endif // GRAPHREADER_H