#include "graphreader.h"
#include "graph.h"
#include "node.h"
#include "stdio.h"
#include "helper.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <osmpbf/blobfile.h>
#include <osmpbf/osmfile.h>
#include <osmpbf/primitiveblockinputadaptor.h>
#include <osmpbf/inode.h>
#include <osmpbf/iway.h>
#include <osmpbf/irelation.h>
#include <osmpbf/parsehelpers.h>
#include <osmpbf/filter.h>
#include <math.h>
#include <chrono>
#include <map>
#include <algorithm>
#include <string>



/*
 * create Offset for outgoing edges
 * if no outgoing edge exists push back -1
 */
int GraphReader::createOffset(Graph* graph)
{
  int current = -1;
  for (int i=0; i < graph->edgecount ; i++){
    if(graph->edges[i].srcID != current ){
      while(graph->edges[i].srcID > current+1){
        graph->offset.push_back(-1);
        current++;
      }
        current++;
        graph->offset.push_back(i);
    }
  }
  return 0;
}
        
/**
 * read file and store data into graphstructure
 */
int GraphReader::read(Graph* graph, char *inputFileName){

    // record time to check time needed for import
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    
    // init file stream
	osmpbf::OSMFileIn inFile(inputFileName, false);
	if (!inFile.open()) {
		std::cout << "Failed to open " <<  inputFileName << std::endl;
		return -1;
	}

    osmpbf::PrimitiveBlockInputAdaptor pbi;
    
    // Add Filter
    osmpbf::KeyMultiValueTagFilter oneWayFilter("oneway",{"yes"});
	osmpbf::AndTagFilter andFilter({
             new osmpbf::KeyMultiValueTagFilter("highway", {"motorway", "motorway_link", "primary", "primary_link", "secondary",
                                                "secondary_link", "tertiary", "tertiary_link", "trunk", "trunk_link", "unclassified", 
                                                "residential", "living_street", "road", "service", "turning_circle"})
    });
    andFilter.assignInputAdaptor(&pbi);
    andFilter.rebuildCache();
    oneWayFilter.rebuildCache();

    // mapping osmID to localID
    std::map<long,int> nodeMap;

    // reading ways
    while(inFile.parseNextBlock(pbi))
    {
        if(pbi.waysSize())
        {
            for(osmpbf::IWayStream way = pbi.getWayStream(); !way.isNull(); way.next()){
                if (andFilter.matches(way))
                {
                    int maxSpeed=0;
                    if(way.tagsSize())
                    {
                        for(uint32_t i = 0, s = way.tagsSize();  i < s; ++i) 
                        {
                            if(way.key(i) == "maxspeed"){
                                try
                                {
                                    maxSpeed = boost::lexical_cast<int>(way.value(i));
                                }
                                catch(boost::bad_lexical_cast &)
                                {
                                    std::cout << "Fehler: " << way.value(i) << std::endl;
                                }
                            } 
                        }

                    }


                    if (way.refsSize())
                    {
                        int srcID;
			            for(osmpbf::RefIterator refIt(way.refBegin()), refEnd(way.refEnd()); refIt != refEnd; ++refIt) 
                        {
                            if(nodeMap.insert({(long)*refIt, graph->nodecount}).second)
                            {
                                graph->nodes.push_back(Node((long)*refIt));
                                graph->nodecount++;
                            }
                            if(refIt == way.refBegin()) 
                            {
                                srcID=*refIt;
                                continue;
                            }
                            if(!oneWayFilter.matches(way))
                            {
                                graph->edges.push_back(Edge(*refIt, srcID));
                                graph->edgecount++;
                            }
                            graph->edges.push_back(Edge(srcID, *refIt));
                            graph->edgecount++;
                            //std::cout << "added Edge. Edgecount: " << graph->edgecount << std::endl;
                            srcID = *refIt;
                        }
                    }
                }
            }
        }

    }

    std::cout << "finished Ways, now fill nodes" << std::endl;

    if (!inFile.open()) return -1;

    // reading nodes
    while(inFile.parseNextBlock(pbi)){
        if(pbi.nodesSize()){
            osmpbf::INodeStream node = pbi.getNodeStream();
            for(osmpbf::INodeStream node = pbi.getNodeStream(); !node.isNull(); node.next())
            {
                if(nodeMap.count(node.id()))
                {
                    graph->nodes[(*nodeMap.find(node.id())).second].lat = node.latd();
                    graph->nodes[(*nodeMap.find(node.id())).second].lon = node.lond();

                }
            }
        }
    }
    
    
    
    
    // time needed for import
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto durationImport = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    
    std::cout << "\n" << std::endl;
    std::cout << "----------Import----------" << std::endl;
    std::cout << "time needed for import: " << durationImport << " microseconds" << std::endl;
    std::cout << "=> " << (durationImport /(long)1000000) << " seconds" << std::endl;
    std::cout << "=> " << (durationImport /(long)60000000) << " minutes" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "\n" << std::endl;

    // Sort and create Offset
    std::sort(graph->edges.begin(), graph->edges.end(), sort_operator());
    GraphReader::createOffset(graph);
    
    // time needed for sort and create Offset
    std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
    auto durationSortAndOffset = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

    std::cout << "--Sort and Create Offset--" << std::endl;
    std::cout << "time needed: " << durationSortAndOffset << " microseconds" << std::endl;
    std::cout << "=> " << (durationSortAndOffset /(long)1000000) << " seconds" << std::endl;
    std::cout << "=> " << (durationSortAndOffset /(long)60000000) << " minutes" << std::endl;
    std::cout << "--------------------------" << std::endl;



    return 1;
}