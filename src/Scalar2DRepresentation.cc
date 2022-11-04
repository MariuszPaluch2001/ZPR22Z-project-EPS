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



std::ostream & operator<<( std::ostream & os, const Scalar2D & sca2d ) {
    return os << sca2d.toString() << "\n";
}