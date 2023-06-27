#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <map>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "wordLadder.hpp"
using namespace std;
// default constructor done for you
WordLadder::WordLadder() = default;

WordLadder::WordLadder(const std::string& inputFile) {
  std::ifstream infile(inputFile);
  std::string word {};
  // Add all words in file to the wordLadder
  while (infile >> word) {
    wordmap.push_back(word);
    addVertex(word);
  }
  //  Add all edges to all the words in the wordLadder
  for (const auto& word : wordmap) {
        for (size_t i = 0; i < word.size(); i++) {
            string neighbour = word;
            for (char c = 'a'; c <= 'z'; c++) {
                if (c != word[i]) {
                    neighbour[i] = c;
                    if (isVertex(neighbour)) {
                        addEdge(word, neighbour);
                    }
                }
            }
        }
    }
}

// add vertex to adjList with empty neighbor set
// if it is not already present.  Otherwise, do nothing.
void WordLadder::addVertex(const std::string& word) {
  if(!isVertex(word)){
    adjList[word] = vector<string>();
  }
}
//Adds each word to each others adjList
void WordLadder::addEdge(const std::string& a, const std::string& b) {
  //addVertex(a);
  //addVertex(b);
  adjList[a].push_back(b);
  adjList[b].push_back(a);
}
//For every word in the words ajList it removes them and then removes the vertex itself
void WordLadder::removeVertex(const std::string& a) {
  if(isVertex(a)){
    for(auto& kv : adjList){
      auto& neighbours = kv.second;
      for(auto it = neighbours.begin(); it != neighbours.end();){
        if(*it == a){
          it =neighbours.erase(it);
        }
        else{
          it++;
        }
      }
    }
    adjList.erase(a);
  }
}
//Checks the first vertex's adjList for the other vertex
bool WordLadder::isEdge(const std::string& a, const std::string& b)  {
  if(isVertex(a)){
    for(const auto& neighbour : adjList[a]){
      if(neighbour == b){
        return true;
      }
    }
  }
  return false;
}
//Checks whether a Vertex exists by counting if it is found
bool WordLadder::isVertex(const std::string& a) const {
  return adjList.count(a) > 0;
}
//Uses Dijkstra's to work through the created adjList and find the getShortestPath
//the algorithm works by going through each potential path steping through each one once
//each loop each path is stopped looking through if it finds an already visited vertex
//it ends when the destination is reached first for a path
std::vector<std::string>
WordLadder::getShortestPath(const std::string& origin, const std::string& dest) {
  queue<string> q;
  unordered_map<string,string> parent;
  unordered_set<string> visited;
  q.push(origin);
  visited.insert(origin);
  parent[origin] = "";
  while(!q.empty()){
    string curr = q.front();
    q.pop();
    if(curr == dest){
      vector<string> path;
      while(curr != ""){
        path.push_back(curr);
        curr = parent[curr];
      }
      reverse(path.begin(), path.end());
      return path;
    }
    for(const auto& neighbour : adjList[curr]){
      if(visited.count(neighbour) == 0){
        q.push(neighbour);
        visited.insert(neighbour);
        parent[neighbour] = curr;
      }
    }
    
  }
  return vector<string>();      
}
//Uses a depth first search to count all the connections
//between all vertex's in the adjList
std::map<std::string, int> WordLadder::listComponents() {
    std::map<std::string, int> components;
    std::unordered_set<std::string> visited;

    for (const auto& [word, _] : adjList) {
        if (visited.count(word) == 0) {
            int componentSize = dfs(word, visited);
            components[word] = componentSize;
        }
    }

    return components;
}
//Counts the number of new(not visited) connections for a word in the adjList
int WordLadder::dfs(const string curr, unordered_set<string>& visited){
    visited.insert(curr);
    int componentSize = 1;
    for (const auto& neighbour : adjList.at(curr)) {
        if (visited.count(neighbour) == 0) {
            componentSize += dfs(neighbour,visited);
        }
    }
    return componentSize;
}

