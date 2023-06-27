#include <fstream>
#include <utility>
#include <functional>
#include <vector>
#include <set>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>
#include <random>
#include "graph.hpp"

// *** for you to implement
double islandHop(const Graph& G) {
  int n = G.numVertices();
  std::vector<double> dp(n, std::numeric_limits<double>::infinity());
  dp[0] = 0.0;
  for(int i = 0; i < n; i++){
    if(i+1<n){
      double cost = G.getEdgeWeight(i, i+1);
      if(cost != std::numeric_limits<double>::infinity()){
        dp[i+1] = std::min(dp[i+1], dp[i] + cost);
      }
    }
    if(i+2<n){
      double cost = G.getEdgeWeight(i, i+2);
      if(cost != std::numeric_limits<double>::infinity()){
        dp[i+2] = std::min(dp[i+2], dp[i] + cost);
      }
    }
  }
  return dp[n-1];
}

// Graph member functions
Graph::Graph() = default;

Graph::Graph(int n, std::vector<Edge> vec)
             : adjList {std::vector<std::set<Edge> >(n)} {
  for (const Edge& e : vec) {
    addEdge(e);
  }
}

void Graph::addEdge(const Edge& e) {
  if (e.from >= 0 && e.to >= 0 &&
      e.from < numVertices() && e.to < numVertices()) {
    adjList.at(e.from).insert(e);
  }
}

bool Graph::isEdge(int fromVertex, int toVertex) const {
  if (fromVertex < 0 || toVertex < 0 ||
        fromVertex >= numVertices() || toVertex >= numVertices()) {
    return false;
  }
  for (const Graph::Edge& e : *neighbours(fromVertex)) {
    if (e.to == toVertex) {
      return true;
    }
  }
  return false;
}

double Graph::getEdgeWeight(int fromVertex, int toVertex) const {
  if (fromVertex < 0 || toVertex < 0 ||
        fromVertex >= numVertices() || toVertex >= numVertices()) {
    throw std::out_of_range("from or to vertex out of range");
  }
  for (const Graph::Edge& e : *neighbours(fromVertex)) {
    if (e.to == toVertex) {
      return e.weight;
    }
  }
  throw std::out_of_range("no such edge");
}

void Graph::changeEdgeWeight(const Edge& e, double newWeight) {
  if (e.from < 0 || e.to < 0 ||
        e.from >= numVertices() || e.to >= numVertices()) {
    return;
  }
  if (!adjList.at(e.from).contains(e)) {
    return;
  }
  adjList.at(e.from).erase(e);
  adjList.at(e.from).insert({newWeight, e.from, e.to});
}

int Graph::numVertices() const {
  return static_cast<int>(adjList.size());
}

// generate random instances like those used by marker
Graph generateRandomIslandInstance(int N, unsigned seed) {
  std::mt19937 mt {seed};
  std::uniform_real_distribution<double> dist {-1.0, 1.0};
  Graph G {N};
  for (int i = 0; i < N - 2; ++i) {
    G.addEdge({dist(mt), i, i + 1});
    G.addEdge({2 * dist(mt), i, i + 2});
  }
  G.addEdge({dist(mt), N - 2, N - 1});
  return G;
}

// print out adjacency list of a Graph
std::ostream& operator<<(std::ostream& out, const Graph& G) {
  for (Graph::iterator it = G.begin(); it != G.end(); ++it) {
    std::cout << it - G.begin() << ':';
    for (const Graph::Edge& e : *it) {
      std::cout << e << ' ';
    }
    std::cout << '\n';
  }
  return out;
}

// print out an Edge
std::ostream& operator<<(std::ostream& out, const Graph::Edge& e) {
  out << '(' << e.from  << ", " << e.to << ")[" << e.weight << ']';
  return out;
}
