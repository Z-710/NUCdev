#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "graph.hpp"

TEST(islandTest, TwoIslands) {
  const int N {2};
  Graph G {N};
  const double weight = 3.14;
  G.addEdge({weight, 0, 1});
  EXPECT_DOUBLE_EQ(islandHop(G), weight);
}

TEST(islandTest, ThreeIslands) {
  const int N {3};
  Graph G {N};
  const double w01 = 0.67;
  const double w12 = 0.32;
  const double w02 = 1.0;
  G.addEdge({w01, 0, 1});
  G.addEdge({w12, 1, 2});
  G.addEdge({w02, 0, 2});
  EXPECT_DOUBLE_EQ(islandHop(G), std::min(w01 + w12, w02));
}

TEST(islandTest, equalEdgeWeightsFiveIslands) {
  const int N {5};
  Graph G {N};
  for (int i = 0; i < N - 2; ++i) {
    G.addEdge({1, i, i + 1});
    G.addEdge({1, i, i + 2});
  }
  G.addEdge({1, N - 2, N - 1});
  EXPECT_DOUBLE_EQ(islandHop(G), 2);
}

TEST(islandTest, equalEdgeWeightsSixIslands) {
  const int N {6};
  Graph G {N};
  for (int i = 0; i < N - 2; ++i) {
    G.addEdge({1, i, i + 1});
    G.addEdge({1, i, i + 2});
  }
  G.addEdge({1, N - 2, N - 1});
  EXPECT_DOUBLE_EQ(islandHop(G), 3);
}

TEST(islandTest, SmallStepFirstSixIslands) {
  const int N {6};
  Graph G {N};
  for (int i = 0; i < N - 2; ++i) {
    G.addEdge({1, i, i + 1});
    G.addEdge({1, i, i + 2});
  }
  G.addEdge({1, N - 2, N - 1});
  G.changeEdgeWeight({1, 0, 1}, 0.8);
  EXPECT_DOUBLE_EQ(islandHop(G), 2.8);
}

TEST(islandTest, SmallSecondStepNotTaken) {
  const int N {6};
  Graph G {N};
  for (int i = 0; i < N - 2; ++i) {
    G.addEdge({1, i, i + 1});
    G.addEdge({1, i, i + 2});
  }
  G.addEdge({1, N - 2, N - 1});
  G.changeEdgeWeight({1, 1, 2}, 0.3);
  EXPECT_DOUBLE_EQ(islandHop(G), 3);
}

TEST(islandTest, NegativeWeightSecondStep) {
  const int N {6};
  Graph G {N};
  for (int i = 0; i < N - 2; ++i) {
    G.addEdge({1, i, i + 1});
    G.addEdge({1, i, i + 2});
  }
  G.addEdge({1, N - 2, N - 1});
  G.changeEdgeWeight({1, 1, 2}, -0.1);
  EXPECT_DOUBLE_EQ(islandHop(G), 2.9);
}

TEST(islandTest, MixedOneHopWeightsSixIslands) {
  const int N {6};
  Graph G {N};
  // make 2 hop edges
  for (int i = 0; i < N - 2; ++i) {
    G.addEdge({1, i, i + 2});
  }
  // weights for one hop edges 
  const std::vector<double> weights {1.18, -0.37, -0.36, -0.07, 1.09};
  for (int i = 0; i < N - 1; ++i) {
    G.addEdge({weights.at(i), i, i + 1});
  }
  EXPECT_DOUBLE_EQ(islandHop(G), 1.45);
}

TEST(islandTest, MixedOneHopWeightsSevenIslands) {
  const int N {7};
  Graph G {N};
  // make 2 hop edges
  for (int i = 0; i < N - 2; ++i) {
    G.addEdge({1, i, i + 2});
  }
  // weights for one hop edges 
  const std::vector<double> weights {-0.16, -0.09, 1.47, -0.25, 1.16, 1.18};
  for (int i = 0; i < N - 1; ++i) {
    G.addEdge({weights.at(i), i, i + 1});
  }
  EXPECT_DOUBLE_EQ(islandHop(G), 1.59);
}

TEST(islandTest, MixedOneHopWeightsEightIslands) {
  const int N {8};
  Graph G {N};
  // make 2 hop edges
  for (int i = 0; i < N - 2; ++i) {
    G.addEdge({1, i, i + 2});
  }
  // weights for one hop edges 
  const std::vector<double> weights 
    {1.47, 1.01, 1.33, -0.16, 1.45, 1.2, -0.38};
  for (int i = 0; i < N - 1; ++i) {
    G.addEdge({weights.at(i), i, i + 1});
  }
  EXPECT_DOUBLE_EQ(islandHop(G), 2.62);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
