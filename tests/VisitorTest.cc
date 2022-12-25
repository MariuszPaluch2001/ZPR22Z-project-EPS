//
// Created by kacper on 10.12.2022.
//
#include "DifferenceVisitor.h"
#include "MidpointVisitor.h"
#include <cmath>
#include <gtest/gtest.h>

/// midpoint visitors




TEST(VisitorTest, TestLeftLineMidpointVisitLeftLine) {
    auto m = MidpointLeftLineVisitor(LeftOrientedLineCommand({1, 1}));
    m.visit(LeftOrientedLineCommand({1,1}));
    auto var = m.getValue();
    auto new_line_pointer = std::get_if<LeftOrientedLineCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 2);
    ASSERT_FLOAT_EQ(mp.getY(), 2);

}

TEST(VisitorTest, TestLeftLineMidpointVisitRightLine) {
    auto m = MidpointLeftLineVisitor(LeftOrientedLineCommand({1, 1}));
    m.visit(RightOrientedLineCommand({1,1}));
    auto var = m.getValue();
    auto new_line_pointer = std::get_if<LeftOrientedLineCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);

}

TEST(VisitorTest, TestLeftLineMidpointVisitPoint) {
    auto m = MidpointLeftLineVisitor(LeftOrientedLineCommand({1, 1}));
    m.visit(PointCommand({1,1}));
    auto var = m.getValue();
    auto new_line_pointer = std::get_if<LeftOrientedLineCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 2);
    ASSERT_FLOAT_EQ(mp.getY(), 2);

}

TEST(VisitorTest, TestRightMidpointVisitLeftLine) {
    auto m = MidpointRightLineVisitor(RightOrientedLineCommand({1, 1}));
    m.visit(LeftOrientedLineCommand({1,1}));
    auto var = m.getValue();
    auto new_line_pointer = std::get_if<RightOrientedLineCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);
}

TEST(VisitorTest, TestRightMidpointVisitRightLine) {
    auto m = MidpointRightLineVisitor(RightOrientedLineCommand({1, 1}));
    m.visit(RightOrientedLineCommand({1,1}));
    auto var = m.getValue();
    auto new_line_pointer = std::get_if<RightOrientedLineCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 2);
    ASSERT_FLOAT_EQ(mp.getY(), 2);
}

TEST(VisitorTest, TestRightMidpointVisitPoint) {
    auto m = MidpointRightLineVisitor(RightOrientedLineCommand({1, 1}));
    m.visit(PointCommand({1,1}));
    auto var = m.getValue();
    auto new_line_pointer = std::get_if<RightOrientedLineCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 2);
    ASSERT_FLOAT_EQ(mp.getY(), 2);
}




TEST(VisitorTest, TestPointMidpointVisitLeftLine) {
    auto m = MidpointPointVisitor(PointCommand({1, 1}));
    m.visit(LeftOrientedLineCommand({1,1}));
    auto var = m.getValue();
    auto new_line_pointer = std::get_if<PointCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);
}

TEST(VisitorTest, TestPointMidpointVisitRightLine) {
    auto m = MidpointPointVisitor(PointCommand({1, 1}));
    m.visit(RightOrientedLineCommand({1,1}));
    auto var = m.getValue();
    auto new_line_pointer = std::get_if<PointCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);
}

TEST(VisitorTest, TestPointMidpointVisitPoint) {
    auto m = MidpointPointVisitor(PointCommand({1, 1}));
    m.visit(PointCommand({1,1}));
    auto var = m.getValue();
    auto new_line_pointer = std::get_if<PointCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 2);
    ASSERT_FLOAT_EQ(mp.getY(), 2);
}

/// difference visitors

TEST(VisitorTest, DifferencePointVisitPoint) {
    auto p1 = PointCommand({3, 4});
  auto p2 = PointCommand({0, 0});

  auto diff_visitor = DifferencePointVisitor(p1);
  diff_visitor.visit(p2);
  ASSERT_TRUE(abs(diff_visitor.getValue()) < 1e-5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}