#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "postorder.hpp"

/***
Formula: 1 + 1
        +
       / \
      1   1
***/
TEST(postorder, onePlusOne) {
  Node leftOperand {"1"};
  Node rightOperand {"1"};
  Node root {"+", &leftOperand, &rightOperand};
  std::vector<std::string> answer {"1", "1", "+"};
  EXPECT_EQ(postorder(&root), answer);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
