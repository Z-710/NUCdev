#include <algorithm>
#include "height.hpp"

int height(Node* root) {
  if(root == nullptr){
    return -1;
  }
  int left_height =  height(root->left);
  int right_height = height(root->right);
  return std::max(left_height,right_height) +1 ;
}
