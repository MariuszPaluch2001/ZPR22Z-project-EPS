//
// Created by kacper on 10.12.2022.
//
#include "Algorithm.hpp"
#include <cmath>
#include <gtest/gtest.h>

TEST(AlgorithmTest, TestCreateAlgorithm) {
    auto _ = Algorithm(0.01);
    (void)_;
}


TEST(AlgorithmTest, TestGetSetMinDiff) {
  auto a = Algorithm(0.01);
  ASSERT_FLOAT_EQ(a.getMinDifference(), 0.01);
  a.setMinDifference(0.1);
  ASSERT_FLOAT_EQ(a.getMinDifference(), 0.1);
}

TEST(AlgorithmTest, TestSetNegativeDiff) {
    auto a = Algorithm(0.01);
    a.setMinDifference(-0.1);
    ASSERT_FLOAT_EQ(a.getMinDifference(), 0.01);
}

TEST(AlgorithmTest, TestGetSetScalingFactor) {
    auto a = Algorithm(0.01);
    ASSERT_FLOAT_EQ(a.getScalingFactor(), 1);
    a.setScalingFactor(0.1);
    ASSERT_FLOAT_EQ(a.getScalingFactor(), 0.1);
}

TEST(AlgorithmTest, TestSetNegativeScalingFactor) {
    auto a = Algorithm(0.01);
    a.setScalingFactor(-0.1);
    ASSERT_FLOAT_EQ(a.getMinDifference(), 0.01);
}

TEST(AlgorithmTest, TestGetSetSortingRange) {
    auto a = Algorithm(0.01);
    ASSERT_FLOAT_EQ(a.getSortingRange(), 10);
    a.setSortingRange(5);
    ASSERT_FLOAT_EQ(a.getSortingRange(), 5);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}