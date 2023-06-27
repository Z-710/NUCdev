#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <random>
#include <limits>
#include "graph.hpp"

auto print(const auto& container) {
  for (const auto& x : container) {
    std::cout << x << '\n';
  }
}

TEST(VerifyTest, sizeOne) {
  Graph G(1);
  // distTo[0] must always be 0
  std::vector<int> distTo {0};
  EXPECT_TRUE(verify(distTo, G));
  distTo = {1};
  EXPECT_FALSE(verify(distTo, G));
}

TEST(VerifyTest, smallLine) {
  Graph G(6);
  G.addEdge(0, 1, 1);
  G.addEdge(1, 2, 1);
  G.addEdge(2, 3, 1);
  G.addEdge(3, 4, 1);
  G.addEdge(4, 5, 1);
  std::vector<int> distTo {0, 1, 2, 3, 4, 5};
  EXPECT_TRUE(verify(distTo, G));
  ++distTo.back();
  EXPECT_FALSE(verify(distTo, G));
}

TEST(VerifyTest, smallCyclePlusEdge) {
  Graph G(6);
  G.addEdge(0, 1, 1);
  G.addEdge(1, 2, 1);
  G.addEdge(2, 3, 1);
  G.addEdge(3, 4, 1);
  G.addEdge(4, 5, 1);
  G.addEdge(5, 0, 1);
  G.addEdge(0, 3, 1);
  std::vector<int> distTo {0, 1, 2, 1, 2, 3};
  EXPECT_TRUE(verify(distTo, G));
  distTo.at(3) += 1;
  EXPECT_FALSE(verify(distTo, G));
}

TEST(VerifyTest, smallNegativeWeight) {
  Graph G(4);
  G.addEdge(0, 1, 4); 
  G.addEdge(0, 2, 5); 
  G.addEdge(2, 1, -3); 
  G.addEdge(1, 3, 1); 
  std::vector<int> distTo {0, 2, 5, 3};
  EXPECT_TRUE(verify(distTo, G));
  distTo = {0, 2, 5, 5};
  EXPECT_FALSE(verify(distTo, G));
}

TEST(VerifyTest, negativeStar) {
  Graph G(6);
  G.addEdge(0, 1, 1); 
  G.addEdge(0, 2, 1); 
  G.addEdge(0, 3, 1); 
  G.addEdge(0, 4, 1); 
  G.addEdge(0, 5, 1); 
  G.addEdge(2, 4, -1); 
  G.addEdge(4, 5, -1); 
  std::vector<int> distTo {0, 1, 1, 1, 1, 1};
  EXPECT_FALSE(verify(distTo, G));
  distTo = {0, 1, 1, 1, 0, -1};
  EXPECT_TRUE(verify(distTo, G));
}

TEST(VerifyTest, smallNegativeCycle) {
  Graph G(4);
  G.addEdge(0, 1, 1); 
  G.addEdge(1, 2, 1); 
  G.addEdge(2, 3, 1); 
  G.addEdge(3, 1, -3); 
  std::vector<int> distTo {0, 0, 2, 3};
  EXPECT_FALSE(verify(distTo, G));
}

TEST(VerifyTest, dijkstraFail) {
  Graph G(5);
  G.addEdge(0, 1, 4);
  G.addEdge(1, 2, -2);
  G.addEdge(2, 3, -2);
  G.addEdge(3, 4, 1);
  G.addEdge(0, 3, 2);
  std::vector<int> distTo {0, 4, 2, 0, 3};
  EXPECT_FALSE(verify(distTo, G));
}

/*TEST(VerifyTest, veryLarge) {
  Graph G(5);
  G.addEdge(0, 1, 4);
  G.addEdge(1, 2, -2);
  G.addEdge(2, 3, -2);
  G.addEdge(3, 4, 1);
  G.addEdge(0, 3, 2);
  std::vector<int> distTo {0, 4, 2, 0, 3};
  EXPECT_FALSE(verify(distTo, G));
}*/

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
