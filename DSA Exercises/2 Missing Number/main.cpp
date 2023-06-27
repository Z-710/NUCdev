#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "missing.hpp"

TEST(missing, sizeOneMissingZero) {
  std::vector<int> vec {1};
  EXPECT_EQ(whoIsMissing(vec), 0);
}

TEST(missing, sizeOneMissingOne) {
  std::vector<int> vec {0};
  EXPECT_EQ(whoIsMissing(vec), 1);
}

TEST(missing, sizeFourMissingZero) {
  std::vector<int> vec {3, 2, 4, 1};
  EXPECT_EQ(whoIsMissing(vec), 0);
}

TEST(missing, sizeFourMissingOne) {
  std::vector<int> vec {2, 3, 0, 4};
  EXPECT_EQ(whoIsMissing(vec), 1);
}

TEST(missing, sizeFourMissingTwo) {
  std::vector<int> vec {3, 4, 1, 0};
  EXPECT_EQ(whoIsMissing(vec), 2);
}

TEST(missing, sizeFourMissingThree) {
  std::vector<int> vec {2, 4, 0, 1};
  EXPECT_EQ(whoIsMissing(vec), 3);
}

TEST(missing, sizeFourMissingFour) {
  std::vector<int> vec {0, 1, 2, 3};
  EXPECT_EQ(whoIsMissing(vec), 4);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
