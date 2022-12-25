//
// Created by kacper on 10.12.2022.
//
#include "DifferenceVisitor.h"
#include "MidpointVisitor.h"
#include <cmath>
#include <gtest/gtest.h>

/// midpoint visitors







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
