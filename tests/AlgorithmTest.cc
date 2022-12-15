//
// Created by kacper on 10.12.2022.
//
#include "Algorithm.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(AlgorithmTest, TestCreateAlgorithm) { Algorithm({1, 2}); }

TEST(AlgorithmTest, TestGetResolution) {
  auto a = Algorithm({1, 2});
  auto res = a.getResolution();
  ASSERT_EQ(res.getX(), 1);
  ASSERT_EQ(res.getY(), 2);
}

TEST(Algorithm, TestSetResolution) {
  auto a = Algorithm({1, 2});
  a.setResolution({3, 4});
  auto res = a.getResolution();
  ASSERT_EQ(res.getX(), 3);
  ASSERT_EQ(res.getY(), 4);
}

//@todo test batch processing after implementing it

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}