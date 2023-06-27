#include <vector>
#include "missing.hpp"
#include <iostream>

// When the input vector is of size n 
// you are guaranteed that it contains all 
// of the integers 0, 1, 2, ..., n except for one.
// The goal of whoIsMissing is to return the missing number
int whoIsMissing(const std::vector<int>& vec) {
  int missing = 0;
  int isfound = false;
  int i = 0;
  int j = 0;
  while(((unsigned)i <= vec.size()) && (isfound == false)){
    isfound = true;
    j = 0;
    while((unsigned)j < vec.size()){
      if(i == vec[j]){
        isfound = false;
      }
      j= j+1;
    }
    missing = i;
    i = i+1;
  }
  std::cout << missing;
  return missing;
}
