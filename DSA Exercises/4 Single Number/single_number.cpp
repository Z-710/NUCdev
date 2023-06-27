#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "single_number.hpp"

int singleNumber(const std::vector<int>& vec) {
  std::vector<int> vector = vec;
  std::sort(vector.begin(),vector.end());
  int i=0;
  bool found = false;
  if(vec.size() <= 1){
    return vec[0];
  }
  else{
    while((unsigned)i<vector.size() && found == false){
      found = true;
      if(vector[i] == vector[i+1]){
          found = false;
      }
      if(vector[i] == vector[i-1]){
          found = false;
      }
      i++;
    }   
  }
  return vector[i-1];

}
