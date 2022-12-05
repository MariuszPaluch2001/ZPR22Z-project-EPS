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


class Direction : public Scalar2D {
public:
    Direction( double x, double y ) : Scalar2D(x, y) {}
    virtual std::string toString() const;
    virtual Direction operator/( double div ) const { return Direction(getX() / div, getY() / div); }


};


//@todo rename to Coordinates
class Point : public Scalar2D {
public:
    Point( double x, double y ) : Scalar2D(x, y) {}
    //Point coordinates can't be negative
    virtual void setX( double new_x );
    virtual void setY( double new_y );
    virtual std::string toString() const;
    virtual Point getMidpoint( const Point & p) const;
    virtual Direction operator-( const Point & p ) const { return Direction(getX() - p.getX(),  getY() - p.getY() ); }
    virtual Direction operator+( const Point & p ) const { return Direction(p.getX() + getX(), p.getY() + getY()); }

};


//@todo delete inherition?
class Resolution : public Scalar2D {
public:
    Resolution( unsigned int x, unsigned int y ) : Scalar2D(x, y) {}
    //Resolution can't be negative
    virtual void setX( double new_x );
    virtual void setY( double new_y );
    virtual std::string toString() const;
};

std::ostream & operator<<( std::ostream & os, const Scalar2D & sca2d );
double length(const Direction & d);
Direction normalizeDirection(const Direction & d);
double getDirectionAngle(const Direction & d);
double countDistanceBetweenConjoinedDirections( const Direction & d1, const Direction & d2);
#endif //ZPR_SCALAR2DREPRESENTATION_H
