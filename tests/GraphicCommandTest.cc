//
// Created by kacper on 04.12.2022.
//

#include <gtest/gtest.h>
#include "GraphicCommands.h"

TEST(GraphicCommandTest, TestCeateLeftOrientedLine) {
    auto _ = LeftOrientedLineCommand({1,2});
}

TEST(GraphicCommandTest, TestLeftOrientedLinePointGetter) {
    auto l = LeftOrientedLineCommand({1,2});
    auto p = l.getMovePoint();
    ASSERT_EQ(p.getX(), 1);
    ASSERT_EQ(p.getY(), 2);
}

TEST(GraphicCommandTest, TestLeftOrientedLineStringForm) {
    //@todo
}

//@todo visitor functions

TEST(GraphicCommandTest, TestLeftOrientedLineDirection) {
    auto l = LeftOrientedLineCommand({1,2});
    auto d = l.getDirection();
    ASSERT_EQ(d.getX(), 1);
    ASSERT_EQ(d.getY(), 2);
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}