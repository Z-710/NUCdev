#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "quicksort.hpp"

// shorten the name so we don't have to
// write the namespace Quicksort::vecIter
using vecIter = Quicksort::vecIter;

// Lomuto Partition as given in lecture 4.7
vecIter lomutoPartition(vecIter begin, vecIter end) {
  vecIter leftEnd = begin + 1;
  for (vecIter j = begin + 1; j < end; ++j) {
    if (*j <= *begin) {
      std::swap(*leftEnd, *j);
      ++leftEnd;
    }
  }
  std::swap(*begin, *(leftEnd-1));
  return leftEnd - 1;
}

// basic quicksort using Lomuto Partition
void Quicksort::basic(vecIter begin, vecIter end) {
  if (end - begin <= 1) {
    return;
  }
  vecIter pivotIt = lomutoPartition(begin, end);
  basic(begin, pivotIt);
  basic(pivotIt+1, end);
}


void Quicksort::insertionSortBaseCase(vecIter begin, vecIter end) {
  // your implementation goes here
  std::swap(*begin,*std::min_element(begin,end));
  for(vecIter i = begin; (i=i+1) < end; begin = i){
    for(vecIter j = i; *j < *begin; (j=j-1), (begin = begin-1)){
      std::swap(*begin,*j);
    }
  }
  
}

void Quicksort::median3InsertionSortBaseCase(vecIter begin, vecIter end) {
  // your implementation goes here
  if(end <=begin){
    return;
  }
  vecIter pivotIt = begin, mid = begin + 1;
  for(vecIter i = begin +1; i<end; i++){
    if(*i < *pivotIt){
      std::swap(*i,*mid);
      mid++;
    }
  }
  std::swap(*begin,*(mid-1));
  median3InsertionSortBaseCase(begin,mid -1);
  median3InsertionSortBaseCase(mid,end);
}

void Quicksort::thirdVariation(vecIter begin, vecIter end) {
  // your implementation goes here
  if(end<= (begin+1)){
    return;
  }
  vecIter mid = begin + (end-begin)/2;
  thirdVariation(begin,mid);
  thirdVariation(mid,end);
  std::inplace_merge(begin,mid,end);

}

void Quicksort::mySort(vecIter begin, vecIter end) {
  // you can call your different functions from here 
  // to test them in main.
  //basic(begin, end);
  //insertionSortBaseCase(begin,end);
  //median3InsertionSortBaseCase(begin,end);
  thirdVariation(begin,end);
}
