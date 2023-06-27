#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <string>
#include <set>
#include <vector>

// Class for directed graphs with edge weights
class Graph {
 public:
  struct Edge {
    double weight {};
    int from {};
    int to {};
    auto operator<=>(const Edge&) const = default;
  };

 private:
  std::vector<std::set<Edge> > adjList {};

 public:
  // default constructor
  Graph();
  // construct graph with n vertices and optionally provide
  // a vector of edges
  explicit Graph(int n, std::vector<Edge> = {});

  void addEdge(const Edge&);
  // change weight of edge e to newWeight
  void changeEdgeWeight(const Edge& e, double newWeight);
  bool isEdge(int, int) const;
  double getEdgeWeight(int, int) const;
  int numVertices() const;

  // let the user interface with the graph via a const iterator
  // const so they can't change our graph with the iterator
  using iterator = std::vector<std::set<Edge> >::const_iterator;

  // cbegin returns const iterator pointing to first element of adjList
  iterator begin() const {
    return adjList.cbegin();
  }

  iterator end() const {
    return adjList.cend();
  }

  // return iterator to a particular vertex
  iterator neighbours(int a) const {
    return adjList.cbegin() + a;
  }
};

// implement this in graph.cpp
double islandHop(const Graph& G);

// generate test cases like those used by the marker
Graph generateRandomIslandInstance(int N, unsigned seed);

// print out a Graph
std::ostream& operator<<(std::ostream&, const Graph&);
// print out an Edge
std::ostream& operator<<(std::ostream&, const Graph::Edge&);

#endif      // GRAPH_HPP_
