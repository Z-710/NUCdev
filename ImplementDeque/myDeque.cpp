#include <iostream>
#include <vector>
#include <string>
#include<bits/stdc++.h>
#include "myDeque.hpp"

// default constructor (nothing to do here)
template <typename T>
MyDeque<T>::MyDeque() {}

// construct a zero-initialized deque of size n
// uncomment the parameter name when 
// you implement this function
// (we commented it out to silence compiler warnings)
template <typename T>
MyDeque<T>::MyDeque(int n) {
  std::vector<T> vec(n,0);
  backVector = vec;
  if(backVector.size() >1){
    rebalance(n);
  }
  
}

// Constructor from initializer list
// uncomment the parameter name when 
// you implement this function
// (we commented it out to silence compiler warnings)
// Moves all values into backVector before rebalancing moving hald into the frontVector
template <typename T>
MyDeque<T>::MyDeque(std::initializer_list<T> vals) {
  std::vector<T> vec(vals);
  backVector = vals;  
  rebalance(vals.size());
}

// uncomment the parameter name when 
// you implement this function
// (we commented it out to silence compiler warnings)
template <typename T>
void MyDeque<T>::push_back(T val) {
  backVector.push_back(val);
}

// uncomment the parameter name when 
// you implement this function
// (we commented it out to silence compiler warnings)
template <typename T>
void MyDeque<T>::push_front(T val) {
  frontVector.push_back(val);
}
//Removes the back of the backVector by first rebalancing checking if there are elements in the backVector before
//removing the back of the backVector or if there is only one element and it is in the frontVector remove it
//finally rebalances if backVector is now empty
template <typename T>
void MyDeque<T>::pop_back() {
  rebalance(backVector.size());
  if(backVector.size() > 0){
    backVector.pop_back();
  }
  else{
    frontVector.pop_back();
  }
  if(backVector.size() < 1){
    rebalance(frontVector.size());
  }
}
//Same as pop_back but for the frontVector removing the front of the deque and back of the frontVector
template <typename T>
void MyDeque<T>::pop_front() {
  rebalance(backVector.size());
  if(frontVector.size() > 0){
    frontVector.pop_back();
  }
  else{   
    backVector.pop_back();
  }
  if(frontVector.size() < 1){
    rebalance(backVector.size());
  }
}
// Returns the back element of the backVector unless the backVector is empty 
// then it returns the element in the frontVector
template <typename T>
T& MyDeque<T>::back() {
  if(backVector.size() > 0){
    return backVector[backVector.size()-1];
  }
  else{
    return frontVector[0];
  }
  
}
template <typename T>
const T& MyDeque<T>::back() const {
  if(backVector.size() > 0){
    return backVector[backVector.size()-1];
  }
  else{
    return frontVector[0];
  }
}
//Returns the front fo the deque by returning the back of the frontVector
template <typename T>
T& MyDeque<T>::front() {
  if(frontVector.size() > 0){
    return frontVector[frontVector.size()-1];
  }
  else{
    return backVector[0];
  }
}
template <typename T>
const T& MyDeque<T>::front() const {
  if(frontVector.size() > 0){
    return frontVector[frontVector.size()-1];
  }
  else{
    return backVector[0];
  }
  
}
//Return true if the sum of the backVector and frontVector size == 0
template <typename T>
bool MyDeque<T>::empty() const {
  if(frontVector.size() + backVector.size() == 0){
    return true;
  }
  else{
    return false;
  }
}
template <typename T>
int MyDeque<T>::size() const {
  return frontVector.size() + backVector.size();
}

template <typename T>
T& MyDeque<T>::operator[](int i) {
  if((unsigned)i<frontVector.size()){
    return(frontVector[frontVector.size()-i-1]);
  }
  else{
    return(backVector[i-frontVector.size()]);
  }
}

template <typename T>
const T& MyDeque<T>::operator[](int i) const {
  if((unsigned)i<=frontVector.size()){
    return(frontVector[frontVector.size()-i-1]);
  }
  else{
    return(backVector[i-frontVector.size()]);
  }
}
//rebalances the two vectors by moving the elements of one to the other if one vector is empty
template <typename T>
void MyDeque<T>::rebalance(int n){
  int i = 0;
  //if the front vector is empty elements move (n+1)/2 elements  into the a temp vector and others into the frontVector 
  if(frontVector.size() < 1){
    std::vector<T> temp;
    while(i < n){
      if(i<(n+1)/2){
        temp.push_back(backVector.back());
        backVector.pop_back();
      }
      else{
        frontVector.push_back(backVector.back());
        backVector.pop_back();
      }    
      i++;      
    }
    //Move elements from the tempVector back into the backVector
    while(temp.size() != 0){
      backVector.push_back(temp.back());
      temp.pop_back();
    }   
  }
  //If the back vector is empty  move (n+1)/2 elements from the frontVector into the a temp vector and others into the backVector
  else if(backVector.size() < 1){
    std::vector<T> temp;
    while(i < n){
      if(i<(n+1)/2){
        temp.push_back(frontVector.back());
        frontVector.pop_back();
      }
      else{
        backVector.push_back(frontVector.back());
        frontVector.pop_back();
      }  
      i++;
    }
    //move elements from temp vector back into frontVector
    while(temp.size() != 0){
      frontVector.push_back(temp.back());
      temp.pop_back();
    }
    
  }
}
// Do not modify these lines.
// They are needed for the marker.
template class MyDeque<int>;
template class MyDeque<double>;
template class MyDeque<char>;
template class MyDeque<std::string>;
