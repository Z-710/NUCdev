#ifndef WORD_LADDER_HPP_
#define WORD_LADDER_HPP_

#include <vector>
#include <string>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class WordLadder {
 private:
  // put whatever member variables you want to represent the graph here
  unordered_map<string, vector<string>> adjList;
  std::vector<std::string> wordmap;
  int dfs(const string curr, unordered_set<string>& visited);
 public:
  WordLadder();
  // construct word graph from words given in filename
  explicit WordLadder(const std::string& filename);

  // add vertex a to the graph with no neighbours if a is
  // not already a vertex.  Otherwise, do nothing.
  void addVertex(const std::string& a);
  // if both a and b are vertices in the graph then add
  // an edge between them.  Otherwise do nothing.
  void addEdge(const std::string& a, const std::string& b);
  // check if there is an edge between words a and b
  bool isEdge(const std::string& a, const std::string& b);
  // check if a is a vertex
  bool isVertex(const std::string& a) const;
  // remove vertex a from the graph
  void removeVertex(const std::string& a);

  // solve the word ladder problem between origin and dest.
  // output a vector whose first element is origin, last element is dest,
  // and where each intermediate word is a valid word and differs from the
  // previous one by a single letter. Moreover the size of this vector
  // should be as small as possible, i.e. it lists vertices on a shortest
  // path from origin to dest. If there is no path between origin and dest
  // return an empty vector.
  std::vector<std::string>
  getShortestPath(const std::string& origin, const std::string& dest);

  // compute all the connected components in the graph.  The output is
  // a std::map<std::string, int>.  The size of the map should be the
  // number of connected components.  For each connected component give the
  // name of a word in the connected component (the std::string part of the
  // pair) and the number of words in that connected component (the int part).
  std::map<std::string, int> listComponents();

 private:
  // you can add any additional helper functions you might need.
};

#endif      // WORD_LADDER_HPP_
