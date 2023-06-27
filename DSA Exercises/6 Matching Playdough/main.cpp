#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "playdough.hpp"

TEST(LastBallTest, allDistinctWeights) {
  std::vector<int> weights {6, 2, 3, 5, 1};
  EXPECT_EQ(lastBallWeight(weights), 1);
}

TEST(LastBallTest, twoEqualWeights) {
  std::vector<int> weights {2, 2};
  EXPECT_EQ(lastBallWeight(weights), 0);
}

TEST(LastBallTest, alreadyPairedUp) {
  std::vector<int> weights {5, 6, 2, 5, 1, 6, 2, 1};
  EXPECT_EQ(lastBallWeight(weights), 0);
}

TEST(LastBallTest, bigGaps) {
  std::vector<int> weights {8, 2, 4, 32, 1, 16, 64};
  EXPECT_EQ(lastBallWeight(weights), 1);
}

TEST(LastBallTest, notOneAtEnd) {
  std::vector<int> weights {9, 3, 5, 33, 17, 65};
  EXPECT_EQ(lastBallWeight(weights), 2);
}

TEST(LastBallTest, biggerNumbers) {
  std::vector<int> weights {45, 98, 21, 111, 32};
  EXPECT_EQ(lastBallWeight(weights), 5);
}

TEST(LastBallTest, twoSetsOfDuplicates) {
  std::vector<int> weights {5, 6, 5, 6, 5, 6, 6, 5};
  EXPECT_EQ(lastBallWeight(weights), 0);
}

TEST(LastBallTest, excessMatchesExisting) {
  std::vector<int> weights {89, 45, 44, 90, 103, 22, 35};
  EXPECT_EQ(lastBallWeight(weights), 0);
}

TEST(LastBallTest, excessMatchesExisting2) {
  std::vector<int> weights {94, 2, 78, 83, 99, 5, 3};
  EXPECT_EQ(lastBallWeight(weights), 0);
}

TEST(LastBallTest, excessMatchesExisting3) {
  std::vector<int> weights {94, 78, 83, 99, 5, 3};
  EXPECT_EQ(lastBallWeight(weights), 2);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

