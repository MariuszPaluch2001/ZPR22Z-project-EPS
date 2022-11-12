#include <gtest/gtest.h>
#include "Scalar2DRepresentation.h"

TEST(Scalar2DRepresentationTest, TestPointCordsGetters)
{
    Point p(2,5);
    ASSERT_EQ(p.getX(), 2);
    ASSERT_EQ(p.getY(), 5);
}

TEST(Scalar2DRepresentationTest, TestDirectionCordsGetters)
{
    Direction d(1,1);
    ASSERT_EQ(d.getX(), 1);
    ASSERT_EQ(d.getY(), 1);
}

TEST(Scalar2DRepresentationTest, TestResolutionCordsGetters)
{
    Resolution r(6,8);
    ASSERT_EQ(r.getX(), 6);
    ASSERT_EQ(r.getY(), 8);
}

TEST(Scalar2DRepresentationTest, TestPointToString)
{
    Point p(3,5);
    ASSERT_TRUE(p.toString() == "Point: (3, 5)");
}

TEST(Scalar2DRepresentationTest, TestDirectionToString)
{
    Direction d(4,2);
    ASSERT_TRUE(d.toString() == "Direction vector: (4, 2)");
}

TEST(Scalar2DRepresentationTest, TestResolutionToString)
{
    Resolution r(7,10);
    ASSERT_TRUE(r.toString() == "Resolution: 7p x 10p");
}

TEST(Scalar2DRepresentationTest, TestPointSetXY)
{
    Point p(1,1);
    p.setX(4);
    p.setY(12);
    ASSERT_EQ(p.getX(), 4);
    ASSERT_EQ(p.getY(), 12);
}

TEST(Scalar2DRepresentationTest, TestResolutionSetXY)
{
    Resolution r(7,10);
    r.setX(5);
    r.setY(9);
    ASSERT_EQ(r.getX(), 5);
    ASSERT_EQ(r.getY(), 9);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
