#include <iostream>
#include <fstream>
#include <utility>
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <limits>
#include <deque>
#include "graph.hpp"

// verify returns true if distTo[i] is the length of a shortest path from 
// vertex 0 to vertex i in the graph G, and false otherwise.  Return false 
// if G contains a negative weight cycle.
// assumptions: 
//   1. All vertices are reachable from 0
//   2. distTo[i] is an upper bound on the length of a shortest path 
//        from 0 to i
// *** For you to implement
bool verify(const std::vector<int>& distTo, const Graph& G) {
  int n = G.size();
  std::vector<int> dist(n, std::numeric_limits<int>::max());
  dist[0] = 0;

  std::deque<int> queue;
  std::unordered_set<int> inQueue;
  std::vector<int> count(n, 0);

  queue.push_back(0);
  inQueue.insert(0);

  while (!queue.empty()) {
    int u = queue.front();
    queue.pop_front();
    inQueue.erase(u);

    for (const auto& [v, weight] : *(G.neighbours(u))) {
      int newDist = dist[u] + weight;

      if (dist[u] != std::numeric_limits<int>::max() && dist[v] > newDist) {
        dist[v] = newDist;

        if (inQueue.find(v) == inQueue.end()) {
          if (++count[v] >= n) {
            return false; // Negative weight cycle detected
          }
          if (!queue.empty() && dist[v] < dist[queue.front()]) {
            queue.push_front(v);
          } else {
            queue.push_back(v);
          }
          inQueue.insert(v);
        }
      }
    }
  }

  // Verify the shortest paths
  for (int i = 0; i < n; ++i) {
    if (distTo[i] != dist[i]) {
      return false; // There is a shorter path than claimed by distTo
    }
  }

  return true;
}

// construct empty graph with n vertices
Graph::Graph(int n) : 
    adjList {std::vector<std::unordered_map<int, int> >(n)} {}

void Graph::addEdge(int from, int to, int weight) {
  int n = size();
  if (from >= 0 && from < n && to >= 0 && to < n) {
    adjList.at(from).insert({to, weight});
  }
}

int Graph::size() const {
  return static_cast<int>(adjList.size());
}

std::ostream& operator<<(std::ostream& out, const Graph& G) {
  for (int i = 0; i < G.size(); ++i) {
    out << i << ':';
    for (const auto& [neighbour, weight] : *(G.neighbours(i))) {
      out << " (" << i << ", " << neighbour << ")[" << weight << ']';
    }
    out << '\n';
  }
  return out;
}

