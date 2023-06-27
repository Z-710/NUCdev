#include <string>
#include <algorithm>
#include "same_letters.hpp"
#include <iostream>
#include <vector>

// given two strings, return true if and only if they contain 
// exactly the same letters including repetition.
bool sameLetters( const std::string& firstString, const std::string& secondString) {
  std::string St1 = firstString;
  std::string St2 = secondString;
  std::sort(St1.begin(),St1.end());
  std::sort(St2.begin(),St2.end());
  for(int i =0;(long unsigned)i<St1.size(); i++){
    if (St1[i] != St2[i]){
      return false;
    }
  }
  for(int i =0;(long unsigned)i<St2.size(); i++){
    if (St2[i] != St1[i]){
      return false;
    }
  }
  return true;
}


