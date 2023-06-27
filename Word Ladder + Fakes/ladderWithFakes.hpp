#ifndef LADDER_WITH_FAKES_HPP_
#define LADDER_WITH_FAKES_HPP_

#include <vector>
#include <string>
#include <queue>
#include <list>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
using namespace std;
class LadderWithFakes {
 private:
  // add some private member variables if needed
    std::unordered_set<std::string> validWords;
    unordered_map<string, vector<string>> adjList;
    std::vector<std::string> wordmap;
    void addVertex(const std::string& a);
    void addEdge(const std::string& a, const std::string& b);
    bool isVertex(const std::string& a) const;
    bool isDiffByK(string word1, string word2, int);
    string createfakeword(string word1, string word2);
    void appendEdges(string, int);
    bool isEdge(const std::string& a, const std::string& b);
 public:
  LadderWithFakes();

  // initialise any private member variables you want 
  // in order to be ready to compute shortest paths with fakes
  explicit LadderWithFakes(const std::string&);

  // given two strings and a budget of fake words k, find the shortest 
  // path between the two strings using at most k fake words
  std::vector<std::string>
  shortestPathWithFakes(const std::string&, const std::string&, int k);
};

#endif      // LADDER_WITH_FAKES_HPP_
