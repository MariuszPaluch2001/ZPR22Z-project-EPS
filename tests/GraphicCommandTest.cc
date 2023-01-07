//
// Created by kacper on 04.12.2022.
//
#include "GraphicCommands.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(GraphicCommandTest, TestCreateLeftLine) {
  auto _ = LeftLineCommand({1, 2});
}

TEST(GraphicCommandTest, TestLeftLinePointGetter) {
  auto l = LeftLineCommand({1, 2});
  auto p = l.getMovePoint();
  ASSERT_EQ(p.getX(), 1);
  ASSERT_EQ(p.getY(), 2);
}

TEST(GraphicCommandTest, TestLeftLineStringForm) {
  auto l = LeftLineCommand({1, 2});
  ASSERT_EQ(l.toString(), std::string("1 2 lineto"));
}


TEST(GraphicCommandTest, TestLeftLineDirection) {
  auto l = LeftLineCommand({1, 2});
  auto d = l.getMovePoint();
  ASSERT_EQ(d.getX(), 1);
  ASSERT_EQ(d.getY(), 2);
}

TEST(GraphicCommandTest, TestCreateRightLine) {
  auto _ = RightLineCommand({1, 2});
}

TEST(GraphicCommandTest, TestRightLinePointGetter) {
  auto r = RightLineCommand({1, 2});
  auto p = r.getMovePoint();
  ASSERT_EQ(p.getX(), 1);
  ASSERT_EQ(p.getY(), 2);
}

TEST(GraphicCommandTest, TestRightLineStringForm) {
  auto r = RightLineCommand({1, 2});
  ASSERT_EQ(r.toString(), std::string("1 2 l"));
}



TEST(GraphicCommandTest, TestRightLineDirection) {
  auto r = RightLineCommand({1, 2});
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

TEST(GraphicCommandTest, TestCreateMoveCommand) {
    auto _ = MoveCommand({1,2});
}


TEST(GraphicCommandTest, TestMoveCommandPointGetter) {
    auto m = MoveCommand({1, 2});
    auto p = m.getMovePoint();
    ASSERT_EQ(p.getX(), 1);
    ASSERT_EQ(p.getY(), 2);
}

TEST(GraphicCommandTest, TestMoveCommandStringForm) {
   ///@todo
}


TEST(GraphicCommandTest, TestRescaleLeftLine) {
    auto ll = LeftLineCommand({2,2});
    ll.rescale(0.5);
    auto p = ll.getMovePoint();
    ASSERT_FLOAT_EQ(p.getX(), 1);
    ASSERT_FLOAT_EQ(p.getY(), 1);

}

TEST(GraphicCommandTest, TestRescaleRightLine) {
    auto rl = RightLineCommand({2,2});
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



TEST(GraphicCommandTest, TestLeftLeftDifference) {
    auto ll1 = LeftLineCommand({1, 1});
    auto ll2 = LeftLineCommand({2, 2});
    auto diff = countDifference(ll1,ll2);
    ASSERT_FLOAT_EQ(diff, 0);
}

TEST(GraphicCommandTest, TestLeftLeftDifferencePerpendicular) {
    auto ll1 = LeftLineCommand({1, 0});
    auto ll2 = LeftLineCommand({0, 2});
    auto diff = countDifference(ll1,ll2);
    ASSERT_TRUE(abs(diff - length(ll2.getMovePoint())) < 1e-5);
}
TEST(GraphicCommandTest, TestLeftLeftMidpoint) {
    auto ll1 = LeftLineCommand({1,1});
    auto ll2 = LeftLineCommand({1,1});
    auto midpoint = createMidpoint(ll1, ll2);
    auto new_line_pointer = std::get_if<LeftLineCommand>(&midpoint);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 2);
    ASSERT_FLOAT_EQ(mp.getY(), 2);
}

TEST(GraphicCommandTest, TestLeftRighttDifference) {
    auto ll = LeftLineCommand({1, 1});
    auto rl = RightLineCommand({-1, -1});
    auto diff = countDifference(ll, rl);
    ASSERT_TRUE(abs(diff - MAX_DIFFERENCE) < 1e-5);
}

TEST(GraphicCommandTest, TestLeftRightMidpoint) {
    auto ll = LeftLineCommand({1,1});
    auto rl = RightLineCommand({-1,-1});
    auto var = createMidpoint(ll,rl);
    auto new_line_pointer = std::get_if<LeftLineCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);
}

TEST(GraphicCommandTest, TestRightLeftDifference) {
    auto rl = RightLineCommand({1,1});
    auto ll = LeftLineCommand({1,1});
    auto diff = countDifference(rl, ll);
    ASSERT_TRUE(abs(diff - MAX_DIFFERENCE) < 1e-5);
}

TEST(GraphicCommandTest, TestRighLefttMidpoint) {
    auto rl = RightLineCommand({1, 1});
    auto ll = LeftLineCommand({1, 1});
    auto var = createMidpoint(rl,ll);
    auto new_line_pointer = std::get_if<RightLineCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);
}

TEST(GraphicCommandTest, TestRightRightDifference) {
    auto rl1 = RightLineCommand({1, 1});
    auto rl2 = RightLineCommand({2, 2});
    auto diff = countDifference(rl1, rl2);
    ASSERT_FLOAT_EQ(diff, 0);
}

TEST(GraphicCommandTest, TestRightRightMidpoint) {
    auto rl1 = RightLineCommand({1,1});
    auto rl2 = RightLineCommand({1,1});
    auto var = createMidpoint(rl1, rl2);
    auto new_line_pointer = std::get_if<RightLineCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 2);
    ASSERT_FLOAT_EQ(mp.getY(), 2);
}

TEST(GraphicCommandTest, TestPointPointDifference) {
    auto p1 = PointCommand({1,1});
    auto p2 = PointCommand({2,2});
    auto diff = countDifference(p1,p2);
    ASSERT_FLOAT_EQ(diff, std::sqrt(2));
}

TEST(GraphicCommandTest, TestPointPointMidpoint) {
    auto p1 = PointCommand({1,1});
    auto p2 = PointCommand({2,2});
    auto var = createMidpoint(p1, p2);
    auto new_line_pointer = std::get_if<PointCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 2);
    ASSERT_FLOAT_EQ(mp.getY(), 2);
}

TEST(GraphicCommandTest, TestPointMoveDifference) {
    auto p1 = PointCommand({1,1});
    auto m2 = MoveCommand({0,0});
    auto diff = countDifference(p1, m2);
    ASSERT_FLOAT_EQ(diff, std::sqrt(2));
}

TEST(GraphicCommandTest, TestPointMoveMidpoint) {
    auto p1 = PointCommand({1,1});
    auto m2 = MoveCommand({2,2});
    auto var = createMidpoint(p1, m2);
    auto new_line_pointer = std::get_if<PointCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 2);
    ASSERT_FLOAT_EQ(mp.getY(), 2);
}

TEST(GraphicCommandTest, TestMovePointDifference) {
    auto m1 = MoveCommand({0,0});
    auto p2 = PointCommand({1,1});
    auto diff = countDifference(m1, p2);
    ASSERT_FLOAT_EQ(diff, 0);
}

TEST(GraphicCommandTest, TestMovePointMidpoint) {
    auto m1 = MoveCommand({2,2});
    auto p2 = PointCommand({1,1});

    auto var = createMidpoint(m1, p2);
    auto new_line_pointer = std::get_if<PointCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);
}

TEST(GraphicCommandTest, TestMoveMoveDifference) {
    auto m1 = MoveCommand({0,0});
    auto m2 = MoveCommand({1,1});
    auto diff = countDifference(m1, m2);
    ASSERT_FLOAT_EQ(diff, 0);
}

TEST(GraphicCommandTest, TestMoveMoveMidpoint) {
    auto m1 = MoveCommand({2,2});
    auto m2 = MoveCommand({1,1});

    auto var = createMidpoint(m1, m2);
    auto new_line_pointer = std::get_if<MoveCommand>(&var);
    ASSERT_TRUE(new_line_pointer != nullptr);
    auto mp = new_line_pointer->getMovePoint();
    ASSERT_FLOAT_EQ(mp.getX(), 1);
    ASSERT_FLOAT_EQ(mp.getY(), 1);
}





int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}