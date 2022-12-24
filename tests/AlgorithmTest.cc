//
// Created by kacper on 10.12.2022.
//
#include "Algorithm.hpp"
#include <cmath>
#include <gtest/gtest.h>

TEST(AlgorithmTest, TestCreateAlgorithm) { Algorithm(0.01); }

TEST(AlgorithmTest, TestGetResolution) {
  auto a = Algorithm(0.01);
  auto res = a.getMinDifference();
  ASSERT_FLOAT_EQ(res, 0.01);

}



//@todo test batch processing after implementing it

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}