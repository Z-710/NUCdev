#include <algorithm>
#include <string>
#include <unordered_map>
#include <iostream>
#include "unique.hpp"

std::size_t firstUniqueChar(const std::string& inputString) {
  // write your solution here
  std::unordered_map<char, std::size_t> map{};
  std::size_t i = 0;
  while( i < inputString.size()){
     map[inputString[i]]++;
     i++;
  }
  for(i = 0; i <inputString.size(); i++){
    for(auto j = map.begin();j !=map.end(); j++){
      if(j-> first == inputString[i] && j -> second == 1){
        return i;
      }
    }
  }
  //std::cout << inputString.size();
  return inputString.size();
}
  

