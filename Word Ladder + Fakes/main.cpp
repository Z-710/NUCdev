#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "ladderWithFakes.hpp"

class TestFakes : public :: testing::Test {
 protected:
  LadderWithFakes G {"4words.txt"};
};

TEST_F(TestFakes, dyadAndAble) {
  std::string origin {"dyad"};
  std::string dest {"able"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_LE(path.size(), 8u);
  EXPECT_GE(path.size(), 5u);
}

TEST_F(TestFakes, bangAndPlow) {
  std::string origin {"bang"};
  std::string dest {"plow"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 5u);
}

TEST_F(TestFakes, palsAndDrop) {
  std::string origin {"pals"};
  std::string dest {"drop"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 5u);
}

TEST_F(TestFakes, noonAndRube) {
  std::string origin {"noon"};
  std::string dest {"rube"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_LE(path.size(), 6u);
  EXPECT_GE(path.size(), 5u);
}

TEST_F(TestFakes, noonAndRube2Fakes) {
  std::string origin {"noon"};
  std::string dest {"rube"};
  int fakes = 2;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 5u);
}

TEST_F(TestFakes, catsAndPawn) {
  std::string origin {"cats"};
  std::string dest {"pawn"};
  int fakes = 0;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 4u);
}

TEST_F(TestFakes, hikeAndFend) {
  std::string origin {"hike"};
  std::string dest {"fend"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 5u);
}

TEST_F(TestFakes, finsAndDyed) {
  std::string origin {"fins"};
  std::string dest {"dyed"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 5u);
}

TEST_F(TestFakes, drawAndColt) {
  std::string origin {"draw"};
  std::string dest {"colt"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 5u);
}

TEST_F(TestFakes, kakaAndPeal) {
  std::string origin {"kaka"};
  std::string dest {"peal"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_LE(path.size(), 7);
  EXPECT_GE(path.size(), 5);
}

TEST_F(TestFakes, kakaAndPealTwoFakes) {
  std::string origin {"kaka"};
  std::string dest {"peal"};
  int fakes = 2;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_LE(path.size(), 6);
  EXPECT_GE(path.size(), 5);
}

TEST_F(TestFakes, quayAndClop) {
  std::string origin {"quay"};
  std::string dest {"clop"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 5u);
}

TEST_F(TestFakes, babaAndVein) {
  std::string origin {"baba"};
  std::string dest {"vein"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_LE(path.size(), 6u);
  EXPECT_GE(path.size(), 5u);
}

TEST_F(TestFakes, babaAndVeinTwoFakes) {
  std::string origin {"baba"};
  std::string dest {"vein"};
  int fakes = 2;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 5u);
}

TEST_F(TestFakes, swagAndAtop) {
  std::string origin {"swag"};
  std::string dest {"atop"};
  int fakes = 1;
  std::vector<std::string>
    path = G.shortestPathWithFakes(origin, dest, fakes);
  EXPECT_EQ(path.size(), 5u);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
