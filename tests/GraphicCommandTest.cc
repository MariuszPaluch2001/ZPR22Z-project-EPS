//
// Created by kacper on 04.12.2022.
//
#include <gtest/gtest.h>
#include "GraphicCommands.h"


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

//@todo visitor functions

TEST(GraphicCommandTest, TestLeftOrientedLineDirection) {
  auto l = LeftOrientedLineCommand({1, 2});
  auto d = l.getDirection();
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

//@todo visitor functions

TEST(GraphicCommandTest, TestRightOrientedLineDirection) {
  auto r = RightOrientedLineCommand({1, 2});
  auto d = r.getDirection();
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
  ASSERT_EQ(pc.toString(), "1 2 1.00 1.00 r p2");
}

//@todo visitor functions

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}