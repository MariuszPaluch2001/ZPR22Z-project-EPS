//
// Created by kacper on 04.11.2022.
//

#include "Scalar2DRepresentation.h"
#include <sstream>
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

void Point::setX( double new_x ) {
    //@todo maybe exception?
    if (new_x >= 0)
        Scalar2D::setX(new_x);
}

void Point::setY( double new_y ) {
    //@todo maybe exception?
    if (new_y >= 0)
        Scalar2D::setY(new_y);
}
std::ostream & operator<<( std::ostream & os, const Scalar2D & sca2d ) {
    return os << sca2d.toString() << "\n";
}