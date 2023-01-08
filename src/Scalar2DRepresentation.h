//
// Created by kacper on 04.11.2022.
// File contains classes representing entity from linear algebra having two
// values - (x,y)
//

#ifndef ZPR_SCALAR2DREPRESENTATION_H
#define ZPR_SCALAR2DREPRESENTATION_H
#include <iostream>

class CoordinateValue {
  double x_, y_;

public:
  CoordinateValue(double x, double y) : x_(x), y_(y) {}
  std::string toString() const;
  double getX() const { return x_; }
  double getY() const { return y_; }
  void setX(double new_x) { x_ = new_x; }
  void setY(double new_y) { y_ = new_y; }
  CoordinateValue operator+(const CoordinateValue &d) const;
  CoordinateValue operator-(const CoordinateValue &d) const;
  CoordinateValue operator/(double div) const;
  CoordinateValue operator*(double scale) const;
};

using Direction = CoordinateValue;
using Coordinates = CoordinateValue;

class Resolution {
  unsigned x_;
  unsigned y_;

public:
  Resolution(unsigned int x, unsigned int y) : x_(x), y_(y) {}
  unsigned getX() const { return x_; }
  unsigned getY() const { return y_; }
  void setX(unsigned new_x) { x_ = new_x; }
  void setY(unsigned new_y) { y_ = new_y; }
  std::string toString() const;
  Resolution operator*(double scale) const;
};
std::ostream &operator<<(std::ostream &os, const Resolution &res);
std::ostream &operator<<(std::ostream &os, const CoordinateValue &cv);

double length(const Direction &d);
Direction normalizeDirection(const Direction &d);

/*
 * Function returns the angle of the Direction in radians
 * */
double getDirectionAngle(const Direction &d);
/*
 * Function projects first Direction on the extension of first Direction
 *  and counts the height of the projection in the farthest point
 */
double countDistanceBetweenConjoinedDirections(const Direction &d1,
                                               const Direction &d2);
#endif // ZPR_SCALAR2DREPRESENTATION_H
