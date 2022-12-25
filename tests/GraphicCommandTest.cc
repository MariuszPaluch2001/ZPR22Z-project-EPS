//
// Created by kacper on 04.12.2022.
//
#include "GraphicCommands.h"
#include <gtest/gtest.h>

TEST(GraphicCommandTest, TestCreateLeftOrientedLine) {
  auto _ = LeftOrientedLineCommand({1, 2});
}

TEST(GraphicCommandTest, TestLeftOrientedLinePointGetter) {
  auto l = LeftOrientedLineCommand({1, 2});
  auto p = l.getMovePoint();
  ASSERT_EQ(p.getX(), 1);
  ASSERT_EQ(p.getY(), 2);
}

TEST(GraphicCommandTest, TestLeftOrientedLineStringForm) {
  auto l = LeftOrientedLineCommand({1, 2});
  ASSERT_EQ(l.toString(), std::string("1 2 lineto"));
}


TEST(GraphicCommandTest, TestLeftOrientedLineDirection) {
  auto l = LeftOrientedLineCommand({1, 2});
  auto d = l.getMovePoint();
  ASSERT_EQ(d.getX(), 1);
  ASSERT_EQ(d.getY(), 2);
}

TEST(GraphicCommandTest, TestCreateRightOrientedLine) {
  auto _ = RightOrientedLineCommand({1, 2});
}

TEST(GraphicCommandTest, TestRightOrientedLinePointGetter) {
  auto r = RightOrientedLineCommand({1, 2});
  auto p = r.getMovePoint();
  ASSERT_EQ(p.getX(), 1);
  ASSERT_EQ(p.getY(), 2);
}

TEST(GraphicCommandTest, TestRightOrientedLineStringForm) {
  auto r = RightOrientedLineCommand({1, 2});
  ASSERT_EQ(r.toString(), std::string("1 2 l"));
}



TEST(GraphicCommandTest, TestRightOrientedLineDirection) {
  auto r = RightOrientedLineCommand({1, 2});
  auto d = r.getMovePoint();
  ASSERT_EQ(d.getX(), 1);
  ASSERT_EQ(d.getY(), 2);
}

TEST(GraphicCommandTest, TestCreatePointCommand) {
  auto _ = PointCommand({1, 2});
}

TEST(GraphicCommandTest, TestPointCommandPointGetter) {
  auto pc = PointCommand({1, 2});
  auto p = pc.getMovePoint();
  ASSERT_EQ(p.getX(), 1);
  ASSERT_EQ(p.getY(), 2);
}

TEST(GraphicCommandTest, TestPointCommandStringForm) {
  auto pc = PointCommand({1, 2});
  ASSERT_EQ(pc.toString(), "1 2 1 1 r p2");
}



TEST(GraphicCommandTest, TestRescaleLeftLine) {
    auto ll = LeftOrientedLineCommand({2,2});
    ll.rescale(0.5);
    auto p = ll.getMovePoint();
    ASSERT_FLOAT_EQ(p.getX(), 1);
    ASSERT_FLOAT_EQ(p.getY(), 1);

}

TEST(GraphicCommandTest, TestRescaleRightLine) {
    auto rl = RightOrientedLineCommand({2,2});
    rl.rescale(2);
    auto p = rl.getMovePoint();
    ASSERT_FLOAT_EQ(p.getX(), 4);
    ASSERT_FLOAT_EQ(p.getY(), 4);
}

TEST(GraphicCommandTest, TestRescalePointCommand) {
    auto pc = PointCommand({2,2});
    pc.rescale(0);
    auto p = pc.getMovePoint();
    ASSERT_FLOAT_EQ(p.getX(), 0);
    ASSERT_FLOAT_EQ(p.getY(), 0);
}

static auto extractMovePoint = [](const auto & gc) {return gc.getMovePoint();};


TEST(GraphicCommandTest, TestLeftLeftDifference) {
    auto ll1 = LeftOrientedLineCommand({1, 1});
    auto ll2 = LeftOrientedLineCommand({2, 2});
    auto diff = countDifference(ll1,ll2);
    ASSERT_FLOAT_EQ(diff, 0);
}

TEST(GraphicCommandTest, TestLeftLeftDifferencePerpendicular) {
    auto ll1 = LeftOrientedLineCommand({1, 0});
    auto ll2 = LeftOrientedLineCommand({0, 2});
    auto diff = countDifference(ll1,ll2);
    ASSERT_TRUE(abs(diff - length(ll2.getMovePoint())) < 1e-5);
}
TEST(GraphicCommandTest, TestLeftLeftMidpoint) {

}

TEST(GraphicCommandTest, TestLeftRighttDifference) {
    auto ll = LeftOrientedLineCommand({1, 1});
    auto rl = RightOrientedLineCommand({-1, -1});
    auto diff = countDifference(ll, rl);
    ASSERT_TRUE(abs(diff - MAX_DIFFERENCE) < 1e-5);
}

TEST(GraphicCommandTest, TestLeftRightMidpoint) {

}

TEST(GraphicCommandTest, TestRightLeftDifference) {
    auto ll = LeftOrientedLineCommand({1, 1});
    auto rl = RightOrientedLineCommand({-1, -1});
    auto diff = countDifference(rl, ll);
    ASSERT_TRUE(abs(diff - MAX_DIFFERENCE) < 1e-5);
}

TEST(GraphicCommandTest, TestRighLefttMidpoint) {

}

TEST(GraphicCommandTest, TestRightRightDifference) {
    auto rl1 = RightOrientedLineCommand({1, 1});
    auto rl2 = RightOrientedLineCommand({2, 2});
    auto diff = countDifference(rl1, rl2);
    ASSERT_FLOAT_EQ(diff, 0);
}

TEST(GraphicCommandTest, TestRightRightMidpoint) {

}

TEST(GraphicCommandTest, TestPointPointDifference) {

}

TEST(GraphicCommandTest, TestPointPointMidpoint) {

}

TEST(GraphicCommandTest, TestPointMoveDifference) {

}

TEST(GraphicCommandTest, TestPointMoveMidpoint) {

}

TEST(GraphicCommandTest, TestMovePointDifference) {

}

TEST(GraphicCommandTest, TestMovePointMidpoint) {

}

TEST(GraphicCommandTest, TestMoveMoveDifference) {

}

TEST(GraphicCommandTest, TestMoveMoveMidpoint) {

}





int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}