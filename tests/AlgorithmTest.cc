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
    AbsoluteBatch batch;
    batch.push_back(PointCommand({0,0}));
    batch.push_back(PointCommand({4,4}));
    batch.push_back(PointCommand({1,1}));
    batch.push_back(PointCommand({4,4}));
    batch.push_back(PointCommand({4,4}));
    batch.push_back(PointCommand({0,0}));
    auto a = Algorithm(1,1,5);

    a.sortBatch(batch);
    auto new_move_point = std::visit(extractMovePoint,batch.at(0));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 0);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 0);

    new_move_point = std::visit(extractMovePoint,batch.at(1));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 1);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 1);

    new_move_point = std::visit(extractMovePoint,batch.at(2));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 4);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 4);

    new_move_point = std::visit(extractMovePoint,batch.at(3));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 4);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 4);

    new_move_point = std::visit(extractMovePoint,batch.at(4));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 4);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 4);

    new_move_point = std::visit(extractMovePoint,batch.at(5));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 0);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 0);
}

TEST(AlgorithmTest, TestSortAbsoluteBatchTooSmall) {
    AbsoluteBatch batch;
    batch.push_back(PointCommand({0,0}));
    batch.push_back(PointCommand({4,4}));
    batch.push_back(PointCommand({1,1}));
    batch.push_back(PointCommand({4,4}));
    batch.push_back(PointCommand({4,4}));
    batch.push_back(PointCommand({0,0}));
    auto a = Algorithm(1,1,10);

    a.sortBatch(batch);
    auto new_move_point = std::visit(extractMovePoint,batch.at(0));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 0);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 0);

    new_move_point = std::visit(extractMovePoint,batch.at(1));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 4);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 4);

    new_move_point = std::visit(extractMovePoint,batch.at(2));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 1);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 1);

    new_move_point = std::visit(extractMovePoint,batch.at(3));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 4);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 4);

    new_move_point = std::visit(extractMovePoint,batch.at(4));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 4);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 4);

    new_move_point = std::visit(extractMovePoint,batch.at(5));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 0);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 0);
}

TEST(AlgorithmTest, TestProcessAbsoluteBatch) {
    AbsoluteBatch batch;
    batch.push_back(PointCommand({0,0}));
    batch.push_back(PointCommand({4,4}));
    batch.push_back(PointCommand({1,1}));
    batch.push_back(PointCommand({4,4}));
    batch.push_back(PointCommand({4,4}));
    batch.push_back(PointCommand({0,0}));
    auto a = Algorithm(1,1,5);
    a.rescaleBatch(batch);
    a.sortBatch(batch);
    batch = a.processBatch(batch);
    ASSERT_EQ(batch.size(), 4);
    auto new_move_point = std::visit(extractMovePoint,batch.at(0));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 0);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 0);

    new_move_point = std::visit(extractMovePoint,batch.at(1));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 1);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 1);

    new_move_point = std::visit(extractMovePoint,batch.at(2));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 4);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 4);

    new_move_point = std::visit(extractMovePoint,batch.at(3));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 0);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 0);
}

TEST(AlgorithmTest, TestProcessAbsoluteBatchTooSmall) {
    auto a = Algorithm(1);
    AbsoluteBatch batch;
    batch = a.processBatch(batch);
    ASSERT_EQ(batch.size(), 0);
    batch.push_back(PointCommand({1,1}));
    batch = a.processBatch(batch);
    ASSERT_EQ(batch.size(), 1);
    auto new_move_point = std::visit(extractMovePoint,batch.at(0));
    ASSERT_FLOAT_EQ(new_move_point.getX(), 1);
    ASSERT_FLOAT_EQ(new_move_point.getY(), 1);
}

TEST(AlgorithmTest, TestProcessRelativeBatch) {

}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}