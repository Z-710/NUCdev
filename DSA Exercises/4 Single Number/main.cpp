#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "single_number.hpp"

TEST(SingleNumberTest, sizeOne) {
  std::vector<int> vec {2};
  EXPECT_EQ(singleNumber(vec), 2);
}

TEST(SingleNumberTest, sizeThree) {
  std::vector<int> vec {2, 1, 2};
  EXPECT_EQ(singleNumber(vec), 1);
}

TEST(SingleNumberTest, letterAppearsMoreThanTwice) {
  std::vector<int> vec {2, 1, 2, 2};
  EXPECT_EQ(singleNumber(vec), 1);
}

TEST(SingleNumberTest, threePairsPlusSingle) {
  std::vector<int> vec {2, 1, 2, 3, 1};
  EXPECT_EQ(singleNumber(vec), 3);
}

TEST(SingleNumberTest, singleNumberAppearsFirst) {
  std::vector<int> vec {23, 17, 19, 19, 8, 17, 8};
  EXPECT_EQ(singleNumber(vec), 23);
}

TEST(SingleNumberTest, singleNumberAppearsLast) {
  std::vector<int> vec {19, 17, 19, 19, 8, 17, 8, 23};
  EXPECT_EQ(singleNumber(vec), 23);
}

TEST(SingleNumberTest, singleNumberIsMinimum) {
  std::vector<int> vec {879, 829, 8923, 100, 829, 38, 8923, 879, 100, 829};
  EXPECT_EQ(singleNumber(vec), 38);
}

TEST(SingleNumberTest, singleNumberIsMaximum) {
  std::vector<int> vec {879, 829, 8923, 100, 829, 38, 38, 879, 100, 829};
  EXPECT_EQ(singleNumber(vec), 8923);
}

TEST(SingleNumberTest, lostInTheCrowd) {
  std::vector<int> vec {1, 1, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_EQ(singleNumber(vec), 10);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
