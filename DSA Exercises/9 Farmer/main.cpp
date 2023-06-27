#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "farm.hpp"

TEST(FarmTest, AlreadyAtGoal) {
  Inventory start {0, 10, 0};
  EXPECT_EQ(daysForEggs(start, 10), 0);
}

// starting with one bale of hay
TEST(FarmTest, OneEgg) {
  Inventory start {1, 0, 0};
  EXPECT_EQ(daysForEggs(start, 1), 1);
}

TEST(FarmTest, TwoEggs) {
  Inventory start {1, 0, 0};
  EXPECT_EQ(daysForEggs(start, 2), 1);
}

TEST(FarmTest, ThreeEggs) {
  Inventory start {1, 0, 0};
  EXPECT_EQ(daysForEggs(start, 3), 2);
}

TEST(FarmTest, ThirteenEggs) {
  Inventory start {1, 0, 0};
  EXPECT_EQ(daysForEggs(start, 13), 6);
}

TEST(FarmTest, TwentyEggs) {
  Inventory start {1, 0, 0};
  EXPECT_EQ(daysForEggs(start, 20), 8);
}

TEST(FarmTest, TwentyThreeEggs) {
  Inventory start {1, 0, 0};
  EXPECT_EQ(daysForEggs(start, 23), 8);
}

// starting with k hay we can have (k-1)*k/2 eggs after k days
TEST(FarmTest, StartWith30Hay) {
  const int k = 30;
  Inventory start {k, 0, 0};
  EXPECT_EQ(daysForEggs(start, (k - 1) * k / 2), k);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
