//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_SCALAR2DREPRESENTATION_H
#define ZPR_SCALAR2DREPRESENTATION_H
#include <iostream>
class Scalar2D {
    double x_, y_;
public:
    Scalar2D( double x, double y ) : x_( x ), y_( y ) {}
    double getX() const { return x_; }
    double getY() const { return y_; }
    virtual void setX( double new_x ) { x_ = new_x; }
    virtual void setY( double new_y ) { y_ = new_y; }
    virtual std::string toString() const = 0;
};


std::ostream & operator<<(std::ostream & os, const Scalar2D & sca2d) {
    return os << sca2d.toString() << "\n";
}
#endif //ZPR_SCALAR2DREPRESENTATION_H
