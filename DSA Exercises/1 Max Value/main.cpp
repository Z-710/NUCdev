#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "max.hpp"

TEST(maxTest, vectorOfSizeOne) {
  std::vector<int> vec {3};
  EXPECT_EQ(maxValue(vec), 3);
}

TEST(maxTest, sizeOneNegative) {
  std::vector<int> vec {-100};
  EXPECT_EQ(maxValue(vec), -100);
}

TEST(maxTest, vectorOfSizeTwo) {
  std::vector<int> vec {-10, 5};
  EXPECT_EQ(maxValue(vec), 5);
}

TEST(maxTest, maxIsNegative) {
  std::vector<int> vec {-10, -8, -13, -4};
  EXPECT_EQ(maxValue(vec), -4);
}

TEST(maxTest, maxIsFirst) {
  std::vector<int> vec {10, 5, -13, 9};
  EXPECT_EQ(maxValue(vec), 10);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
