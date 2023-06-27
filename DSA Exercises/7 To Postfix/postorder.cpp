#include <vector>
#include <string>
#include <algorithm>
#include "postorder.hpp"
void recursion(Node*,std::vector<std::string>&);
std::vector<std::string> postorder(Node* root) {
  std::vector<std::string> order{};
  recursion(root,order);
  return order;
}
void recursion(Node* node, std::vector<std::string>& order){
  if(node == nullptr){
    return;
  }
  if(node->left){
    recursion(node->left, order);
  }
  if(node->right){
    recursion(node->right,order);
  }
  order.push_back(node->data);
  return;
}
