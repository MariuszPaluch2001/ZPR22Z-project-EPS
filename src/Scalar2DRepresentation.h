//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_SCALAR2DREPRESENTATION_H
#define ZPR_SCALAR2DREPRESENTATION_H
#include <iostream>
class Scalar2D {
    int x_, y_;
public:
    Scalar2D( int x, int y ) : x_( x ), y_( y ) {}
    int getX() const { return x_; }
    int getY() const { return y_; }
    virtual void setX( int new_x ) { x_ = new_x; }
    virtual void setY( int new_y ) { y_ = new_y; }
    virtual std::string toString() const = 0;
};

class Point : public Scalar2D {
public:
    Point( unsigned int x, unsigned int y ) : Scalar2D(x, y) {}
    //Point coordinates can't be negative
    virtual void setX( int new_x );
    virtual void setY( int new_y );
    virtual std::string toString() const;
};

class Direction : public Scalar2D {
public:
    Direction( int x, int y ) : Scalar2D(x, y) {}
    virtual std::string toString() const;
};

class Resolution : public Scalar2D {
public:
    explicit Resolution( double x = 0, double y = 0 ) : Scalar2D(x, y) {}
    virtual std::string toString() const;
};

std::ostream & operator<<( std::ostream & os, const Scalar2D & sca2d );
#endif //ZPR_SCALAR2DREPRESENTATION_H
