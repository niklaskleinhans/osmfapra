#include "search.h"
#include "edge.h"
#include "node.h"
#include "helper.h"
#include "stdio.h"
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

Search::Search(Graph* graph)
{
  this->graph = graph;
  this->visited = std::vector<bool>(graph->nodes.size(), false);
  this->visitedReversed = std::vector<bool>(graph->nodes.size(), false);
  //this->visitedBy = std::vector<std::pair<bool,bool>>(graph->nodes.size(), std::pair<bool,bool>(false,false));
  this->parents = std::vector<int>(graph->nodes.size(), -1);
  this->parentsReversed = std::vector<int>(graph->nodes.size(), -1);
  this->distances = std::vector<int>(graph->nodes.size(), std::numeric_limits<int>::max());
  this->distancesReversed = std::vector<int>(graph->nodes.size(), std::numeric_limits<int>::max());
}
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

void Search::reset(){
  // TODO clean up!!
  u_int stop = std::max(this->touch_parents.size(), this->touch_visited.size());

  this-> priorityQueue = std::priority_queue<pair<int, int>, std::vector<pair<int, int>>, pair_sort_operator>();
  for (u_int i = 0; i< stop; i++){
    if (this->touch_visited.size() < i){
      this->visited[this->touch_visited[i]] = false;
    }
    if (this->touch_parents.size() < i){
      this->parents[this->touch_parents[i]] = -1;
      this->distances[this->touch_parents[i]] = std::numeric_limits<int>::max();
    }
  }
}

void Search::expand(int source, int costs){
  this->visited[source] = true;
  //this->visitedBy[source] = make_pair(true, get<1>(this->visitedBy[source]));
  this->touch_visited.push_back(source);
  if(this->graph->offset[source] == -1) return;
  for(int i = this->graph->offset[source]; i < this->graph->offset[source+1] ; i++){
    priorityQueue.push(make_pair((this->graph->edges[i].cost + costs), this->graph->edges[i].trgID));
    if(this->distances[this->graph->edges[i].trgID]> this->graph->edges[i].cost + costs){
      this->parents[this->graph->edges[i].trgID] = i;
      this->distances[this->graph->edges[i].trgID] = this->graph->edges[i].cost + costs;
    }
  }
}

void Search::expandReversed(int source, int costs){
  this->visitedReversed[source] = true;
  //this->visitedBy[source] = make_pair(get<0>(this->visitedBy[source]),true);
  this->touch_visited.push_back(source);
  if(this->graph->offsetReversed[source] == -1) return;
  for(int i = this->graph->offsetReversed[source]; i < this->graph->offsetReversed[source+1] ; i++){
    priorityQueueReversed.push(make_pair((this->graph->edgesReversed[i].cost + costs), this->graph->edgesReversed[i].trgID));
    if(this->distancesReversed[this->graph->edgesReversed[i].trgID]> this->graph->edgesReversed[i].cost + costs){
      this->parentsReversed[this->graph->edgesReversed[i].trgID] = i;
      this->distancesReversed[this->graph->edgesReversed[i].trgID] = this->graph->edgesReversed[i].cost + costs;
    }
  }
}


int Search::bestMeetNode(){
  int bestMeetNode = -1;
  int currentSmallestDistance = std::numeric_limits<int>::max();
  for (int i=0; i < this->touch_visited.size() ; i++){
    if (this->distances[touch_visited[i]] < std::numeric_limits<int>::max() && 
        this->distancesReversed[touch_visited[i]]< std::numeric_limits<int>::max()){
      if (this->distances[touch_visited[i]]+ this->distancesReversed[touch_visited[i]] < currentSmallestDistance){
        currentSmallestDistance = this->distances[touch_visited[i]] + this->distancesReversed[touch_visited[i]];
        bestMeetNode = touch_visited[i];
      }
    }
  }
  return bestMeetNode;
}

void Search::oneToOne(int source, int target, Result* result){
  pair<int,int> current;
  pair<int,int> currentReversed;
  this->expand(source, 0);
  if(!this->visited[target])
    this->expandReversed(target, 0);
  while(!this->priorityQueue.empty() && !this->priorityQueueReversed.empty()){
  //while(!this->priorityQueue.empty()){
  //while(!this->priorityQueueReversed.empty()){
    current = priorityQueue.top();
    currentReversed = priorityQueueReversed.top();
    if (get<1>(current) == target ){
      std::cout << get<1>(current) << " " << source << std::endl;
      result->distance = get<0>(current);
      int currNode = target;
      result->path.insert(result->path.begin(), this->graph->nodes[currNode]);
      while (currNode != source){
        currNode = this->graph->edges[this->parents[currNode]].srcID;
        result->pathCost = result->pathCost + this->graph->edges[this->parents[currNode]].cost;
        result->path.insert(result->path.begin(), this->graph->nodes[currNode]);
      }
      break;
    }
    
    if (get<1>(currentReversed) == source ){
      std::cout << "Reveresed: " << get<1>(currentReversed) << " " << source << std::endl;
      result->distance = get<0>(currentReversed);
      int currNode = source;
      result->path.insert(result->path.begin(), this->graph->nodes[source]);
      while (currNode != target){
        currNode = this->graph->edgesReversed[this->parentsReversed[currNode]].srcID;
        result->pathCost = result->pathCost + this->graph->edgesReversed[this->parentsReversed[currNode]].cost;
        result->path.insert(result->path.begin(), this->graph->nodes[currNode]);
      }
      std::reverse(result->path.begin(), result->path.end());
      break;
    }
    if (this->visitedReversed[get<1>(current)] || this->visited[get<1>(currentReversed)]){
      int meetNode = this->bestMeetNode();
      int currNode = meetNode;
      result->pathCost = this->distancesReversed[currNode];
      std::vector<Node> path;
      path.insert(path.begin(), this->graph->nodes[currNode]);
      while (currNode != target){
        currNode = this->graph->edgesReversed[this->parentsReversed[currNode]].srcID;
        //result->pathCost = result->pathCost + this->graph->edgesReversed[this->parentsReversed[currNode]].cost;
        path.insert(path.begin(), this->graph->nodes[currNode]);
      }
      std::reverse(path.begin(), path.end());
      result->path = path;
      currNode = meetNode;
      result->pathCost = result->pathCost + this->distances[currNode]; 
      while (currNode != source){
        currNode = this->graph->edges[this->parents[currNode]].srcID;
        //result->pathCost = result->pathCost + this->graph->edges[this->parents[currNode]].cost;
        result->path.insert(result->path.begin(), this->graph->nodes[currNode]);
      }
      break;
    }
    
    priorityQueue.pop();
    priorityQueueReversed.pop();
    if(!this->visited[get<1>(current)])
      this->expand(get<1>(current), get<0>(current));
    if(!this->visitedReversed[get<1>(currentReversed)])
      this->expandReversed(get<1>(currentReversed), get<0>(currentReversed));
  }
  return;
}

void Search::getPath(int source, int currNode, vector<Node>* path){
      path->insert(path->begin(), this->graph->nodes[currNode]);
      while (currNode != source){
        currNode = this->graph->edges[this->parents[currNode]].srcID;
        path->insert(path->begin(), this->graph->nodes[currNode]);
      }
}