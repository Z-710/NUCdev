#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>

class Graph {
 private:
  std::vector<std::unordered_map<int, int> > adjList {};

 public:
  // construct empty graph with n vertices
  explicit Graph(int n);

  void addEdge(int from, int to, int weight);

  int size() const;

  // this time we let the user interface with the graph via a const iterator
  // const so they can't change our graph with the iterator
  using iterator = 
    std::vector<std::unordered_map<int, int> >::const_iterator;

  // cbegin returns const iterator pointing to first element of adjList
  iterator begin() const {
    return adjList.cbegin();
  }

  iterator end() const {
    return adjList.cend();
  }

  // return iterator to a particular vertex
  iterator neighbours(int a) const {
    return adjList.begin() + a;
  }
};

bool verify(const std::vector<int>& distTo, const Graph& G);

// print out a graph
std::ostream& operator<<(std::ostream&, const Graph&);

#endif      // GRAPH_HPP_
