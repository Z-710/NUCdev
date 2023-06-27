#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "same_letters.hpp"

TEST(SameLettersTest, size3SameLetters) {
  EXPECT_TRUE(sameLetters("abc", "cab"));
}

TEST(SameLettersTest, sameLengthDifferentLetters) {
  EXPECT_FALSE(sameLetters("abc", "def"));
}

TEST(SameLettersTest, allLettersTheSame) {
  EXPECT_FALSE(sameLetters("qqq", "qqqq"));
}

TEST(SameLettersTest, superSet) {
  EXPECT_FALSE(sameLetters("abc", "abcd"));
}

TEST(SameLettersTest, subSet) {
  EXPECT_FALSE(sameLetters("abcd", "abc"));
}

TEST(SameLettersTest, bothEmptyStrings) {
  EXPECT_TRUE(sameLetters("", ""));
}

TEST(SameLettersTest, oneEmptyString) {
  EXPECT_FALSE(sameLetters("", "abc"));
}

TEST(SameLettersTest, singleCharacterStrings) {
  EXPECT_TRUE(sameLetters("a", "a"));
  EXPECT_FALSE(sameLetters("a", "b"));
}

TEST(SameLettersTest, RepeatedLetters) {
  EXPECT_TRUE(sameLetters("aabbc", "bacab"));
}

TEST(SameLettersTest, dontViolateConst) {
  std::string s1 {"tghl"};
  std::string s2 {"lgth"};
  EXPECT_TRUE(sameLetters(s1, s2));
  EXPECT_EQ(s1, "tghl");
  EXPECT_EQ(s2, "lgth");
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

