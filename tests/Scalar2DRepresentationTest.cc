#include <gtest/gtest.h>
#include "Scalar2DRepresentation.h"
#include <cmath>

TEST(Scalar2DRepresentationTest, TestPointCordsGetters)
{
    Point p(2.2,5);
    ASSERT_TRUE(abs(p.getX() - 2.2) < 1e-5);
    ASSERT_TRUE(abs(p.getY() - 5) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestDirectionCordsGetters)
{
    Direction d(6,8.3);
    ASSERT_TRUE(abs(d.getX() - 6) < 1e-5);
    ASSERT_TRUE(abs(d.getY() - 8.3) < 1e-5);
}



TEST(Scalar2DRepresentationTest, TestResolutionCordsGetters)
{
    Resolution r(6,8);
    ASSERT_TRUE(abs(r.getX() - 6) < 1e-5);
    ASSERT_TRUE(abs(r.getY() - 8) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestPointToString)
{
    Point p(3,5);
    ASSERT_TRUE(p.toString() == "Point: (3, 5)");
}

TEST(Scalar2DRepresentationTest, TestDirectionToString)
{
    Direction d(4.5,2);
    ASSERT_TRUE(d.toString() == "Direction vector: (4.5, 2)");
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
    ASSERT_TRUE(abs(p.getX() - 4)<1e-5);
    ASSERT_TRUE(abs(p.getY() - 12)<1e-5);

}

TEST(Scalar2DRepresentationTest, TestResolutionSetXY)
{
    Resolution r(7,10);
    r.setX(5);
    r.setY(9);
    ASSERT_TRUE(abs(r.getX() - 5)<1e-5);
    ASSERT_TRUE(abs(r.getY() - 9)<1e-5);
}

TEST(Scalar2DRepresentationTest, TestDirectionDivOperator) {
    auto d = Direction(3, 4);
    auto divD = d/2;
    ASSERT_TRUE(abs(divD.getX() - 3./2) < 1e-5);
    ASSERT_TRUE(abs(divD.getY() - 2.) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestPointAdditionOperator) {
    auto p1 = Point({3,4});
    auto p2 = Point({2,5});
    auto p3 = p1 + p2;
    ASSERT_TRUE(abs(p3.getX() - 5) < 1e-5);
    ASSERT_TRUE(abs(p3.getY() - 9) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestPointSubtractionOperator) {
    auto p1 = Point({3,4});
    auto p2 = Point({2,5});
    auto p3 = p1 - p2;
    ASSERT_TRUE(abs(p3.getX() - 1) < 1e-5);
    ASSERT_TRUE(abs(p3.getY() + 1) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestOstreamOperator) {
    Point p(3,5);
    std::ostringstream oss;
    oss << p;

    ASSERT_TRUE(oss.str() == "Point: (3, 5)");
}

TEST(Scalar2DRepresentationTest, TestDirectionLength) {
    Direction d1(3,4);
    ASSERT_TRUE(abs(length(d1) - 5) < 1e-5);

    Direction d2(5,6);
    ASSERT_TRUE(abs(length(d2) - std::sqrt(5*5 + 6*6)) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestDirectionZeroLength) {
    Direction d1(0,0);
    ASSERT_TRUE(abs(length(d1) - 0) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestGetMidpoint) {
    auto p1 = Point(2,3);
    auto p2 = Point(1, 7);
    auto p3 = p1.getMidpoint(p2);
    ASSERT_TRUE(abs(p3.getX() - 1.5) < 1e-5);
    ASSERT_TRUE(abs(p3.getY() - 5) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestNormalizeZeroLengthDirection) {
    auto d1 = Direction(0,0);
    auto d2 = normalizeDirection(d1);
    ASSERT_TRUE(abs(d2.getX() - 0) < 1e-5);
    ASSERT_TRUE(abs(d2.getY() - 0) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestNormalizeDirection) {
    auto d1 = Direction(3,4);
    auto d2 = normalizeDirection(d1);
    ASSERT_TRUE(abs(d2.getX() - 0.6) < 1e-5);
    ASSERT_TRUE(abs(d2.getY() - 0.8) < 1e-5);
    ASSERT_TRUE(abs(length(d2) - 1) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestPointSetNegativeValues) {
    auto p = Point(1,2);
    p.setX(-1);
    p.setY(-2.5);
    ASSERT_TRUE(abs(p.getX() - 1) < 1e-5);
    ASSERT_TRUE(abs(p.getY() - 2) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestResolutionSetNegativeValues) {
    auto r = Resolution(1,2);
    r.setX(-2);
    r.setY(-5);
    ASSERT_TRUE(abs(r.getX() - 1) < 1e-5);
    ASSERT_TRUE(abs(r.getY() - 2) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestDirectionZeroAngle) {
    auto d = Direction(1,0);
    auto angle = getDirectionAngle(d);
    ASSERT_FLOAT_EQ(angle, 0);
}

TEST(Scalar2DRepresentationTest, TestDirection90Angle) {
    auto d = Direction(0,1);
    auto angle = getDirectionAngle(d);
    ASSERT_FLOAT_EQ(angle, M_PI/2);
}

TEST(Scalar2DRepresentatioTest, TestDirectionAngle) {
    auto d = Direction(1,1);
    auto angle = getDirectionAngle(d);
    ASSERT_FLOAT_EQ(angle, M_PI/4);
}

TEST(Scalar2DRepresentationTest, TestNegativeXAngle) {
    auto d = Direction(-1,1);
    auto angle = getDirectionAngle(d);
    ASSERT_FLOAT_EQ(angle, 3*M_PI/4);
}

TEST(Scalar2DRepresentationTest, TestNegativeXYAngle) {
    auto d = Direction(-1,-1);
    auto angle = getDirectionAngle(d);
    ASSERT_FLOAT_EQ(angle,   -3*M_PI/4);
}

TEST(Scalar2DRepresentationTest, TestNegativeYAngle) {
    auto d = Direction(1,-1);
    auto angle = getDirectionAngle(d);
    ASSERT_FLOAT_EQ(angle, -M_PI/4);
}

TEST(Scalar2DRepresentatinoTest, TestPIAngle) {
    auto d = Direction(-1,0);
    auto angle = getDirectionAngle(d);
    ASSERT_FLOAT_EQ(angle, M_PI);
}

TEST(Scalar2DRepresentationTest, TestNegative90Angle) {
    auto d = Direction(0, -1);
    auto angle = getDirectionAngle(d);
    ASSERT_FLOAT_EQ(angle, -M_PI/2);
}

TEST(Scalar2DRepresentationTest, TestDistanceBetweenParallelDirections) {
    auto d1 = Direction(1,2);
    auto d2 = Direction(2,4);
    auto res = countDistanceBetweenConjoinedDirections(d1,d2);
    ASSERT_TRUE(abs(res - 0) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestDistanceBetweenPerpendicularDirections) {
    auto d1 = Direction(1,0);
    auto d2 = Direction(0,1);
    auto res = countDistanceBetweenConjoinedDirections(d1,d2);
    ASSERT_FLOAT_EQ(res,1);
}

TEST(Scalar2DRepresentationTest, TestDistanceBetweenOppositDirections) {
    auto d1 = Direction(1,0);
    auto d2 = Direction(-1,0);
    auto res = countDistanceBetweenConjoinedDirections(d1,d2);
    ASSERT_TRUE(abs(res - 0) < 1e-5);
}

TEST(Scalar2DRepresentationTest, TestDistanceBetweenNormalizedDirections) {
    auto d1 = normalizeDirection(Direction(1,0));
    auto d2 = normalizeDirection(Direction(1,1));
    auto res = countDistanceBetweenConjoinedDirections(d1,d2);
    ASSERT_TRUE(abs(res - sqrt(2)/2.) < 1e-5);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
