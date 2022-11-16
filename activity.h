#ifndef ACTIVITY_H
#define ACTIVITY_H

// =========================================================
// File: actitivy.h
// Author: Fernando Matute Soto
// Date: 14/11/2022
// =========================================================

#include "ugraph.h"

// =========================================================
// @dfs2 is a version of depth search using recursivity
//
// Complexity O(n)
// =========================================================
template <class Vertex>
void dfs2(Vertex v, const UnweightedGraph<Vertex>* graph,
    std::set<Vertex> &reached, std::stack<Vertex> &TS) {
  
  typename std::set<Vertex>::iterator itr;
  std::set<Vertex> connections = graph->getConnectionFrom(v);
  reached.insert(v);

  for (itr = connections.begin(); itr != connections.end(); itr++) {
    if (reached.find(*itr) == reached.end()) {
      dfs2(*itr, graph, reached, TS);
    }
  }

  TS.push(v);
}

// =========================================================
// @topologicalSort returns the DAG order of the graph
//
// Complexity O(n)
// =========================================================
template <class Vertex>
std::string topologicalSort(const UnweightedGraph<Vertex>* graph) {
  
  typename std::vector<Vertex>::iterator i;
  std::stringstream aux; // to convert int to string
  std::set<Vertex> reached;  // Elements visited
  std::stack<Vertex> TS; // Result of the topological sort

  bool* visited = new bool[graph->getVertexes().size()];

  std::vector<Vertex> vertexes = graph->getVertexes(); // Get all vertexes

  for (i = vertexes.begin(); i != vertexes.end(); i++) {
    if (reached.find(*i) == reached.end()) {
      dfs2(*i, graph, reached, TS);
    }
  }

  aux << "[";
  while (TS.empty() == false) {
    aux << TS.top() << " ";
    TS.pop();
  }

  aux.seekp(-1, std::ios_base::end);
  aux << "]";

  return aux.str();

}

// =========================================================
// @isBipartite determines if the graph is bipartite or not
//
// Complexity O(n)
// =========================================================
template <class Vertex>
bool isBipartite(const UnweightedGraph<Vertex>* graph) {

  typename std::vector<Vertex>::iterator itr;
  typename std::set<Vertex>::iterator j;
 
  std::vector<Vertex> vertexes = graph->getVertexes();
  std::set<Vertex> visited;
  std::set<Vertex> group1;
  std::set<Vertex> group2;
  std::stack<Vertex> pending;

  for (itr = vertexes.begin(); itr != vertexes.end(); itr++) {
    
    if (visited.find(*itr) == visited.end()) {
      pending.push(*itr);
      group1.insert(*itr);
      
      while (!pending.empty()) {
        Vertex v = pending.top(); pending.pop();
        
        if (visited.find(v) == visited.end()) {
          visited.insert(v);
          std::set<Vertex> connections = graph->getConnectionFrom(v);
          
          for (j = connections.begin(); j != connections.end(); j++) {
            
            if (visited.find(*j) == visited.end()) {
              pending.push(*j);
              
              if (group1.find(v) != group1.end()) {
                group2.insert(*j);
              } else {
                group1.insert(*j);
              }
            } else {
              if (group1.find(v) != group1.end()) {
                if (group1.find(*j) != group1.end()) {
                  return false;
                }
              } else {
                if (group2.find(*j) != group2.end()) {
                  return false;
                }
              }
            }
          }
        }
      }
    }
  }

  return true;
}

// =========================================================
// @isCyclic finds the root of the tree
//
// Complexity O(n)
// =========================================================
template <class Vertex>
bool isCyclic(Vertex v, const UnweightedGraph<Vertex>* graph,
  std::set<Vertex> &reached, Vertex parent) {
  typename std::set<Vertex>::iterator itr;

  if (reached.find(v) != reached.end()) {
    return true;
  }
  reached.insert(v);
  std::set<Vertex> connections = graph->getConnectionFrom(v);
  for (itr = connections.begin(); itr != connections.end(); itr++) {
    if (*itr != parent) {
      if (isCyclic(*itr, graph, reached, v)) {
        return true;
      }
    }
  }

  return false;
}

// =========================================================
// @isTree returns True if the graph forms a tree
//
// Complexity O(n)
// =========================================================
template <class Vertex>
bool isTree(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;

  std::vector<Vertex> vertexes = graph->getVertexes();
  for (itr = vertexes.begin(); itr != vertexes.end(); itr++) {
    std::set<Vertex> reached;
    if (isCyclic(*itr, graph, reached, *itr)) {
      return false;
    }
  }

  return true;
}

#endif /* ACTIVITY_H */