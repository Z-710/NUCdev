#ifndef POSTORDER_HPP_
#define POSTORDER_HPP_

#include <vector>
#include <string>

struct Node {
  std::string data {};
  Node* left {};
  Node* right {};
};

std::vector<std::string> postorder(Node* root);

#endif      // POSTORDER_HPP_
