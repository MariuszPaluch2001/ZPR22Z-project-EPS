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
static auto extractMovePoint = [](const auto & gc) {return gc.getMovePoint();};

TEST(AlgorithmTest, TestAbsoluteBatchRescaling) {
    AbsoluteBatch batch;
    batch.push_back(PointCommand({2,2}));
    batch.push_back(MoveCommand({3,3}));

    auto a = Algorithm(0.01,0.5);
    a.rescaleBatch(batch);
    auto new_move_point = std::visit(extractMovePoint,batch.at(0));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 1);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 1);

    new_move_point = std::visit(extractMovePoint,batch.at(1));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 1.5);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 1.5);
}

TEST(AlgorithmTest, TestRelativeBatchRescaling) {
    RelativeBatch batch;
    batch.push_back(LeftOrientedLineCommand({2,2}));
    batch.push_back(RightOrientedLineCommand({3,3}));

    auto a = Algorithm(0.01,0.5);
    a.rescaleBatch(batch);
    auto new_move_point = std::visit(extractMovePoint,batch.at(0));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 1);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 1);

    new_move_point = std::visit(extractMovePoint,batch.at(1));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 1.5);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 1.5);
}

TEST(AlgorithmTest, TestSortAbsoluteBatch) {

}

TEST(AlgorithmTest, TestProcessAbsoluteBatch) {

}

TEST(AlgorithmTest, TestProcessRelativeBatch) {

}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}