#include <vector>
#include <utility>
#include "nuts_and_bolts.hpp"
#include "match.hpp"
int partition(std::vector<auto>& vec, int low, int high, auto pivot);
void match(std::vector<Nut>& nuts, std::vector<Bolt>& bolts, int low, int high);
int MAX_SIZE_SORT = 10000;
//int total = 0;
void matchNutsAndBolts(std::vector<Nut>& nuts, std::vector<Bolt>& bolts) {
  // implement your solution here.
  int low = 0;
  int high;
  high = nuts.size()-1;
  //std::cout << high;  
  if(high < MAX_SIZE_SORT){
    match(nuts,bolts,low,high);
  }
  /*std::cout << "Nuts: ";
  for(int i = 0; i <= high; i++){
    std::cout << nuts[i]<< ",";   
  }
  std::cout << "\nBolts: ";
  for(int i = 0; i <= high; i++){
    std::cout << bolts[i]<<",";   
  }
  std::cout << "\n";*/
  //std::cout << "Total recursions: " << total;
}
int partition(std::vector<auto>& vec, int low, int high, auto pivot){
  int i = low;
  int repeats = 0;
  for(int j = low; j < high; j++){
    if(vec[j] != pivot){
      std::swap(vec[i],vec[j]);
      i++;    
    }
    else if(vec[j] == pivot){
      std::swap(vec[j],vec[high]);
      if(repeats > 0){
        j++;
      } 
      repeats++;
      j--;
    }
  }
  std::swap(vec[i],vec[high]);
  return i;
}
void match(std::vector<Nut>& nuts, std::vector<Bolt>& bolts, int low, int high){
  if(nuts[low] == bolts[low] && nuts[high] == bolts[high]){
    return;
  }
  if(low<high){
      //std::cout << total<< "\n";
      //total ++;
      int pivot = partition(nuts, low, high, bolts[high]);    
      partition(bolts, low, high, nuts[pivot]); 
      match(nuts,bolts,low,pivot-1);
      match(nuts,bolts,pivot+1,high);
    }
    return;
}

