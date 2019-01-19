#include "search.h"
#include "edge.h"
#include "helper.h"
#include "stdio.h"
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

/**
 * find Node
 * @param Graph graph, double KoordinateX, double KoordinateY
 */
int Search::findNode(Graph *graph, double longitude, double latitude)
{
  int nearestNode;
  double currentShortestDistance=std::numeric_limits<int>::max();
  //std::cout << "testen wir das mal" << longitude << latitude << std::endl;
  for(int i=0; i<graph->nodes.size();i++){
    double tmp = point_distance(longitude, graph->nodes[i].lon,latitude,graph->nodes[i].lat);
    if(tmp < currentShortestDistance){
      currentShortestDistance = tmp;
      nearestNode = i;
        }
    if (double_equals(graph->nodes[i].lat, latitude) && double_equals(graph->nodes[i].lon, longitude)){
      std::cout << "found Node" << std::endl;
      return i;
    }
  }
  std::cout << "found nearest Node: "<< nearestNode << " [" 
  << graph->nodes[nearestNode].lon << ", "
  << graph->nodes[nearestNode].lat << "]" << std::endl;
  return nearestNode;
}

/**
 * Retrun a random Way based on a sourcenodeid
 * @param Graph graph, int srcID
 */
boost::property_tree::ptree Search::randomWayReturn(Graph *graph, int srcID)
{
  int currentNode=srcID;
  int previousNode=-1;
  std::vector<int> result;

  for (int i = 0; i<1000; i++)
  {
    result.push_back(currentNode);
    if(graph->offset[currentNode] == -1) break;
    if(graph->edges[graph->offset[currentNode]].trgID != previousNode)
    {
      previousNode = currentNode;
      currentNode= graph->edges[graph->offset[currentNode]].trgID;
    }else if(graph->edges[graph->offset[currentNode]+1].srcID == currentNode)
    {
      previousNode = currentNode;
      currentNode = graph->edges[graph->offset[currentNode]+1].trgID;
    }else
    {
      break;
    }

  }
  boost::property_tree::ptree matrix_node;
  for (int i = 0; i < result.size(); i++)
    {
      double node [2]= {graph->nodes[result[i]].lon, graph->nodes[result[i]].lat};
      //std::cout << result[i] << " : " << node[0] << " : " << node[1] << std::endl;
      boost::property_tree::ptree row;
      for (int j = 0; j <= 1 ; j++)
        {
          // Create an unnamed value
          boost::property_tree::ptree cell;
          cell.put_value(node[j]);
          // Add the value to our row
          row.push_back(std::make_pair("", cell));
        }
      // Add the row to our matrix
      matrix_node.push_back(std::make_pair("", row));
    }
  return matrix_node;
}

