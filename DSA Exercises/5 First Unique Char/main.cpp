#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "unique.hpp"

TEST(UniqueTest, Empty) {
  std::string word {};
  EXPECT_EQ(firstUniqueChar(word), word.size());
}

TEST(UniqueTest, uniqueAtBeginning) {
  std::string word {"abbcc"};
  // 0u tells compiler to interpret 0 as an
  // unsigned int rather than an int
  // this prevents a compiler warning about
  // comparing an unsigned type against a signed one
  EXPECT_EQ(firstUniqueChar(word), 0u);
}

TEST(UniqueTest, uniqueIsLast) {
  std::string word {"bbcca"};
  EXPECT_EQ(firstUniqueChar(word), word.size()-1);
}

TEST(UniqueTest, allUniqueCharacters) {
  std::string word {"abc[!#>,?"};
  EXPECT_EQ(firstUniqueChar(word), 0u);
}

TEST(UniqueTest, caseMatters) {
  std::string word {"abA"};
  EXPECT_EQ(firstUniqueChar(word), 0u);
}

TEST(UniqueTest, otherCharacters) {
  std::string word {"3483499rdl[]l!d[23r82aq!"};
  EXPECT_EQ(firstUniqueChar(word), 11u);
}

TEST(UniqueTest, someUniqueSomeNot) {
  std::string word {"allbvfcdadefgb"};
  EXPECT_EQ(firstUniqueChar(word), 4u);
}

TEST(UniqueTest, random) {
  std::string word {"lkejlwkdskdslew"};
  EXPECT_EQ(firstUniqueChar(word), 3u);
}

TEST(UniqueTest, noUniqueLetter) {
  std::string word {"aa"};
  EXPECT_EQ(firstUniqueChar(word), word.size());
}

TEST(UniqueTest, longerNoUniqueLetter) {
  std::string word {"lk?e[j!lw[kds]jkds]!lew?"};
  EXPECT_EQ(firstUniqueChar(word), word.size());
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

