#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <queue>
#include <map>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cassert>
#include "ladderWithFakes.hpp"
using namespace std;
// default initialiser does not need to do anything
LadderWithFakes::LadderWithFakes() = default;

// initialise any private member variables you want 
// in order to be ready to compute shortest paths with fakes
// *** put your implementation here
LadderWithFakes::LadderWithFakes(const std::string& inputFile) {
  std::ifstream file(inputFile);
  std::string word;
  while(file >> word){
    validWords.insert(word);
    wordmap.push_back(word);
    addVertex(word);
  }
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
void LadderWithFakes::addVertex(const std::string& word) {
  if(!isVertex(word)){
    adjList[word] = vector<string>();
  }
}

bool LadderWithFakes::isVertex(const std::string& a) const {
  return adjList.count(a) > 0;
}

void LadderWithFakes::addEdge(const std::string& a, const std::string& b) {
  adjList[a].push_back(b);
  adjList[b].push_back(a);
}

// given two strings and a budget of fake words k, find the shortest 
// path between the two strings using at most k fake words
// *** put your implementation here
// To handle the budget of fake words the words which have k+1 letters
// differing from the origin will be added to the origin's adjList neighbours and a k number of
// fake words will be placed between them at the end once a path is found
std::vector<std::string>
LadderWithFakes::shortestPathWithFakes(const std::string& origin,const std::string& dest,int k) {
  /*cout<<"origin is: "<< origin << "\n";
  cout<<"dest is: "<< dest << "\n";*/
  if(k > 0){
    appendEdges(origin, k);
  }
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
      //Pops off the origin and places k amount of
      //fake words in between before pushing the origin
      //back on
      path.pop_back();
      for(int i = 0; i < k; i++){
        path.push_back(createfakeword(path.back(),origin));
      }
      path.push_back(origin);
      reverse(path.begin(), path.end());
      /*
      cout << "path:\n";
      for(string step: path){
        cout << step << ",";
      }
      cout<<"\n";*/

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
  
  /*cout << "empty path\n";*/
  return vector<string>();      
  
}
//Checks if the word has k+1 amount of difference letters to another
bool LadderWithFakes::isDiffByK(string word1, string word2, int k){
  int difference = 0;
  for(int i = 0; i< 4; i++){
      if(word1[i] != word2[i]){
        difference++;
      }
  }
  return difference == k+1;
}
//Creates a word that is in between two words by changing one differing letter 
//of one word into one of the others e.g. bang and blog makes -> baog
string LadderWithFakes::createfakeword(string word1, string word2){
  for(int i = 0; i< 4; i++){
      if(word1[i] != word2[i]){
        word1[i] = word2[i];
        return word1;
      }
  }
  return {};
}
//For the amount of fake words allowed add edges to words that
//are k+1 letters different so that from the origin, fake words can be used
//to skip 
void LadderWithFakes::appendEdges(string origin, int k){
  /*cout<<"appendEdges to:" << origin << "\n";*/
  for(string word : validWords){
    if(isDiffByK(origin, word, k)){
      adjList[origin].push_back(word);
    }
  }
}
//Checks if a vertex has another vertex in their adjList neighbours
bool LadderWithFakes::isEdge(const std::string& a, const std::string& b)  {
  if(isVertex(a)){
    for(const auto& neighbour : adjList[a]){
      if(neighbour == b){
        return true;
      }
    }
  }
  return false;
}
