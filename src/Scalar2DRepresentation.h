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


class Direction : public Scalar2D {
public:
    Direction( double x, double y ) : Scalar2D(x, y) {}
    virtual std::string toString() const;
    virtual Direction operator/( double div ) const { return Direction(getX() / div, getY() / div); }


};


//@todo rename to Coordinates
class Point : public Scalar2D {
public:
    Point( unsigned int x, unsigned int y ) : Scalar2D(x, y) {}
    //Point coordinates can't be negative
    virtual void setX( int new_x );
    virtual void setY( int new_y );
    virtual std::string toString() const;
    virtual Point getMidpoint( const Point & p) const;
    virtual Direction operator-( const Point & p ) const { return Direction(p.getX() - getX(), p.getY() - getY()); }
    virtual Direction operator+( const Point & p ) const { return Direction(p.getX() + getX(), p.getY() + getY()); }

};



class Resolution : public Scalar2D {
public:
    Resolution( unsigned int x, unsigned int y ) : Scalar2D(x, y) {}
    //Resolution can't be negative
    virtual void setX( int new_x );
    virtual void setY( int new_y );
    virtual std::string toString() const;
};

std::ostream & operator<<( std::ostream & os, const Scalar2D & sca2d );
double length(const Direction & d);
Direction normalizeDirection(const Direction & d);
double countDistanceBetweenConjoinedDirections( const Direction & d1, const Direction & d2);
#endif //ZPR_SCALAR2DREPRESENTATION_H
