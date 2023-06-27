#ifndef HEIGHT_HPP_
#define HEIGHT_HPP_

struct Node {
  int val {};
  Node* left {};
  Node* right {};
};

int height(Node* root);

#endif      // HEIGHT_HPP_
