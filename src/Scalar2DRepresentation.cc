//
// Created by kacper on 04.11.2022.
//

#include "Scalar2DRepresentation.h"
#include <sstream>
#include <cmath>
std::string Point::toString() const {
    std::stringstream s;
    s << "Point: (" << getX() << ", " << getY() << ")";
    return s.str();
}

std::string Direction::toString() const {
    std::stringstream s;
    s << "Direction vector: (" << getX() << ", " << getY() << ")";
    return s.str();
}

std::string Resolution::toString() const {
    std::stringstream s;
    s << "Resolution: " << getX() << "p x " << getY() << "p";
    return s.str();
}

void Point::setX( int new_x ) {
    //@todo maybe exception?
    if (new_x >= 0)
        Scalar2D::setX(new_x);
}

void Point::setY( int new_y ) {
    //@todo maybe exception?
    if (new_y >= 0)
        Scalar2D::setY(new_y);
}

void Resolution::setX( int new_x ) {
    //@todo maybe exception?
    if (new_x >= 0)
        Scalar2D::setX(new_x);
}

void Resolution::setY( int new_y ) {
    //@todo maybe exception?
    if (new_y >= 0)
        Scalar2D::setY(new_y);
}

Point Point::getMidpoint(const Point &p) const {
    return Point((p.getX() + getX())/2, (p.getY() + getY())/2);

}

std::ostream & operator<<( std::ostream & os, const Scalar2D & sca2d ) {
    return os << sca2d.toString();
}

double length(const Direction & d) {
    return std::sqrt(std::pow(d.getX(),2) + std::pow(d.getY(), 2));
}

Direction normalizeDirection(const Direction & d) {
    auto len = length(d);
    return len == 0 ? Direction( 0, 0 ) : d / len;
}

double countDistanceBetweenConjoinedDirections( const Direction & d1, const Direction & d2) {
    auto firstNormalisedDirection= normalizeDirection(d1);
    auto secondNormalisedDirection = normalizeDirection(d2);
    //tangent of a normalised vector
    auto tan1 = firstNormalisedDirection.getX() / firstNormalisedDirection.getY();
    auto tan2 = secondNormalisedDirection.getX() / secondNormalisedDirection.getY();
    //using formula for tan(alfa2 - alfa1) to count angle between Direction vectors
    double tangentInBetween = (tan2 - tan1) / (1 + tan1 * tan2);

    return std::sin(std::atan(tangentInBetween)) * length(d2);
}