//
// Created by kacper on 10.12.2022.
//
#include "DifferenceVisitor.h"
#include "MidpointVisitor.h"
#include <cmath>
#include <gtest/gtest.h>

/// midpoint visitors

static auto extractMovePoint = [](const auto & gc) {return gc.getMovePoint();};

TEST(VisitorTest, TestCreateMidpointLeftLineVisitor) {
  auto m = MidpointLeftLineVisitor(LeftOrientedLineCommand({1, 1}));
  auto mp = std::visit(extractMovePoint, m.getValue());
  ASSERT_FLOAT_EQ(mp.getX(), 1);
  ASSERT_FLOAT_EQ(mp.getY(), 1);

}

TEST(VisitorTest, TestCreateMidpointRightLineVisitor) {
  auto m = MidpointRightLineVisitor(RightOrientedLineCommand({1, 1}));
    auto mp = std::visit(extractMovePoint, m.getValue());
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);
}

TEST(VisitorTest, TestCreateMidpointPointVisitor) {
  auto m = MidpointPointVisitor(PointCommand({1, 1}));
    auto mp = std::visit(extractMovePoint, m.getValue());
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);
}



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
TEST(VisitorTest, TestCreateDifferenceLeftLineVisitor) {
  auto _ = DifferenceLeftLineVisitor(LeftOrientedLineCommand({1, 1}));
}

TEST(VisitorTest, TestCreateDifferenceRightLineVisitor) {
  auto _ = DifferenceRightLineVisitor(RightOrientedLineCommand({1, 1}));
}

TEST(VisitorTest, TestCreateDifferencePointVisitor) {
  auto _ = DifferencePointVisitor(PointCommand({1, 1}));
}

TEST(VisitorTest, DifferenceLeftLineVisitLeftLineSameDirection) {
  auto ll1 = LeftOrientedLineCommand({1, 1});
  auto ll2 = LeftOrientedLineCommand({2, 2});
  auto diff_visitor = DifferenceLeftLineVisitor(ll1);
  diff_visitor.visit(ll2);
  ASSERT_TRUE(abs(diff_visitor.getValue() - 0) < 1e-5);
}

TEST(VisitorTest, DifferenceLeftLineVisitLeftLinePerpendicular) {
  auto ll1 = LeftOrientedLineCommand({1, 0});
  auto ll2 = LeftOrientedLineCommand({0, 2});
  auto diff_visitor = DifferenceLeftLineVisitor(ll1);
  diff_visitor.visit(ll2);
  ASSERT_TRUE(abs(diff_visitor.getValue() - length(ll2.getMovePoint())) < 1e-5);
}

TEST(VisitorTest, DifferenceLeftLineVisitRightLine) {
  auto ll = LeftOrientedLineCommand({1, 1});
  auto rl = RightOrientedLineCommand({-1, -1});
  auto diff_visitor = DifferenceLeftLineVisitor(ll);
  diff_visitor.visit(rl);
  ASSERT_TRUE(abs(diff_visitor.getValue() - MAX_DIFFERENCE) < 1e-5);
}

TEST(VisitorTest, DifferenceLeftLineVisitPoint) {
  auto ll = LeftOrientedLineCommand({0, 0});
  auto p = PointCommand({3, 4});
  auto diff_visitor = DifferenceLeftLineVisitor(ll);
  diff_visitor.visit(p);
  ASSERT_TRUE(abs(diff_visitor.getValue() - 5) < 1e-5);
}

TEST(VisitorTest, DifferenceRightLineVisitRightLineSameDirection) {
  auto rl1 = RightOrientedLineCommand({1, 1});
  auto rl2 = RightOrientedLineCommand({2, 2});
  auto diff_visitor = DifferenceRightLineVisitor(rl1);
  diff_visitor.visit(rl2);
  ASSERT_TRUE(abs(diff_visitor.getValue() - 0) < 1e-5);
}

TEST(VisitorTest, DifferenceRightLineVisitRightLinePerpendicular) {
  auto rl1 = RightOrientedLineCommand({1, 0});
  auto rl2 = RightOrientedLineCommand({0, 2});
  auto diff_visitor = DifferenceRightLineVisitor(rl1);
  diff_visitor.visit(rl2);
  ASSERT_TRUE(abs(diff_visitor.getValue() - length(rl2.getMovePoint())) < 1e-5);
}

TEST(VisitorTest, DifferenceRightLineVisitLeftLine) {
  auto ll = LeftOrientedLineCommand({1, 1});
  auto rl = RightOrientedLineCommand({-1, -1});
  auto diff_visitor = DifferenceRightLineVisitor(rl);
  diff_visitor.visit(ll);
  ASSERT_TRUE(abs(diff_visitor.getValue() - MAX_DIFFERENCE) < 1e-5);
}

TEST(VisitorTest, DifferenceRightLineVisitPoint) {
  auto rl = RightOrientedLineCommand({0, 0});
  auto p = PointCommand({3, 4});
  auto diff_visitor = DifferenceRightLineVisitor(rl);
  diff_visitor.visit(p);
  ASSERT_TRUE(abs(diff_visitor.getValue() - 5) < 1e-5);
}

TEST(VisitorTest, DifferencePointVisitLeftLine) {
  auto ll = LeftOrientedLineCommand({1, 2});
  auto p = PointCommand({3, 4});
  auto diff_visitor = DifferencePointVisitor(p);
  diff_visitor.visit(ll);
  ASSERT_TRUE(abs(diff_visitor.getValue() - MAX_DIFFERENCE) < 1e-5);
}

TEST(VisitorTest, DifferencePointVisitRightLine) {
  auto rl = RightOrientedLineCommand({1, 2});
  auto p = PointCommand({3, 4});
  auto diff_visitor = DifferencePointVisitor(p);
  diff_visitor.visit(rl);
  ASSERT_TRUE(abs(diff_visitor.getValue() - MAX_DIFFERENCE) < 1e-5);
}

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