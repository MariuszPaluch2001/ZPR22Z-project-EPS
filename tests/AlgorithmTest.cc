//
// Created by kacper on 10.12.2022.
//
#include <cmath>
#include <gtest/gtest.h>
#include "Algorithm.h"


TEST(AlgorithmTest, TestCreateAlgorithm) { Algorithm({1, 2}); }

TEST(AlgorithmTest, TestGetResolution) {
  auto a = Algorithm({1, 2});
  auto res = a.getResolution();
  ASSERT_TRUE(abs(res.getX() - 1) < 1e-5);
  ASSERT_TRUE(abs(res.getY() - 2) < 1e-5);
}

TEST(Algorithm, TestSetResolution) {
  auto a = Algorithm({1, 2});
  a.setResolution({3, 4});
  auto res = a.getResolution();
  ASSERT_TRUE(abs(res.getX() - 3) < 1e-5);
  ASSERT_TRUE(abs(res.getY() - 4) < 1e-5);
}

//@todo test batch processing after implementing it

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}