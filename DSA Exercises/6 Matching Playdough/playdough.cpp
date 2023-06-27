#include <vector>
#include <queue>
#include <algorithm>
#include <deque>
#include <iostream>
#include "playdough.hpp"

int lastBallWeight(const std::vector<int>& weights) {
  std::priority_queue<int> q;
  std::priority_queue<int> waiting;
  std::size_t i = 0;
  int temp;
  while(i<weights.size()){
    waiting.push(weights[i]); 
    i++;
  }  
  q.push(waiting.top());  
  waiting.pop();
  while(waiting.size() > 0){
    if(q.top() == waiting.top()){
      q.pop();
      waiting.pop();
    }
    else{
      if(waiting.top() > q.top()){
        temp = waiting.top() - q.top();
      }else{
        temp = q.top() - waiting.top();
      }
      q.pop();
      waiting.pop();
      waiting.push(temp);
    }
    if(waiting.size() > 0){
      q.push(waiting.top());  
      waiting.pop();
    }
  }
  if(q.size() == 0){
    return 0;
  }
  else{
    return q.top();
  } 
}

