//
// Created by kacper on 04.11.2022.
// File contains classes representing entity from linear algebra having two
// values - (x,y)
//

#ifndef ZPR_SCALAR2DREPRESENTATION_H
#define ZPR_SCALAR2DREPRESENTATION_H
#include <iostream>
template <typename T> class Scalar2D {
  T x_, y_;

public:
  Scalar2D(T x, T y) : x_(x), y_(y) {}
  T getX() const { return x_; }
  T getY() const { return y_; }
  virtual void setX(T new_x) { x_ = new_x; }
  virtual void setY(T new_y) { y_ = new_y; }
  virtual std::string toString() const = 0;
};

class CoordinateValue : public Scalar2D<double> {
public:
    CoordinateValue(double x, double y) : Scalar2D(x, y) {}
  virtual std::string toString() const override;
    CoordinateValue operator+(const CoordinateValue &d) const;
    CoordinateValue operator-(const CoordinateValue &d) const;
    CoordinateValue operator/(double div) const;
    CoordinateValue operator*(double scale) const;
};

using Direction = CoordinateValue;

class Resolution : public Scalar2D<unsigned int> {
public:
  Resolution(unsigned int x, unsigned int y) : Scalar2D(x, y) {}
  virtual std::string toString() const override;
  virtual Resolution operator*(double scale) const;

};
template <typename T>
std::ostream &operator<<(std::ostream &os, const Scalar2D<T> &sca2d) {
  return os << sca2d.toString();
}

double length(const Direction &d);
Direction normalizeDirection(const Direction &d);
double getDirectionAngle(const Direction &d);
/*
 * Function projects first Direction on the extension of first Direction
 *  and counts the height of the projection in the farthest point
 */
double countDistanceBetweenConjoinedDirections(const Direction &d1,
                                               const Direction &d2);
#endif // ZPR_SCALAR2DREPRESENTATION_H
