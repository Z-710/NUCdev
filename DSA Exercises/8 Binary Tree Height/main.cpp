#include <gtest/gtest.h>
#include <iostream>
#include "height.hpp"

TEST(heightTest, nullptrHeightNegativeOne) {
  Node* root {nullptr};
  EXPECT_EQ(height(root), -1);
}

TEST(heightTest, singleNodeHeightZero) {
  Node root {1};
  EXPECT_EQ(height(&root), 0);
}

TEST(heightTest, heightOneLeftChild) {
  Node leftChild {2};
  Node root {1, &leftChild};
  EXPECT_EQ(height(&root), 1);
}

TEST(heightTest, heightOneRightChild) {
  Node rightChild {2};
  Node root {1, nullptr, &rightChild};
  EXPECT_EQ(height(&root), 1);
}

TEST(heightTest, heightOneBalanced) {
  Node leftChild {2};
  Node rightChild {3};
  Node root {1, &leftChild, &rightChild};
  EXPECT_EQ(height(&root), 1);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
