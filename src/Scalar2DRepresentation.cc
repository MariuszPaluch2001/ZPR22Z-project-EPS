//
// Created by kacper on 04.11.2022.
//
#include "Scalar2DRepresentation.h"
#include <cmath>
#include <sstream>



std::string CoordinateValue::toString() const {
  std::stringstream s;
  s << "CoordinateValue: (" << getX() << ", " << getY() << ")";
  return s.str();
}

std::string Resolution::toString() const {
  std::stringstream s;
  s << "Resolution: " << getX() << "p x " << getY() << "p";
  return s.str();
}
/*
Coordinates Coordinates::getMidpoint(const Coordinates &p) const {
  return Coordinates((p.getX() + getX()) / 2, (p.getY() + getY()) / 2);
}
*/
double length(const Direction &d) {
  return std::sqrt(std::pow(d.getX(), 2) + std::pow(d.getY(), 2));
}

Direction normalizeDirection(const Direction &d) {
  auto len = length(d);
  return len == 0 ? Direction(0, 0) : d / len;
}

double getDirectionAngle(const Direction &d) {
  auto d2 = normalizeDirection(d);
  auto angle = std::asin(d2.getY());
  if (d2.getX() < 0) {
    angle = (angle >= 0 ? M_PI : -M_PI) - angle;
  }
  return angle;
}

//@todo opposite Directions are a fuss
double countDistanceBetweenConjoinedDirections(const Direction &d1,
                                               const Direction &d2) {
  auto firstAngle = getDirectionAngle(d1);
  auto secondAngle = getDirectionAngle(d2);
  auto angleInBetween = secondAngle - firstAngle;
  return std::sin(angleInBetween) * length(d2);
}

CoordinateValue CoordinateValue::operator/(double div) const {
  return div < 1e-5 ? Direction(0, 0) : Direction(getX() / div, getY() / div);
}

CoordinateValue CoordinateValue::operator+(const CoordinateValue &d) const {
    return {getX() + d.getX(), getY() + d.getY()};
}

CoordinateValue CoordinateValue::operator-(const CoordinateValue &d) const {
    return {getX() - d.getX(), getY() - d.getY()};
}
CoordinateValue CoordinateValue::operator*(double scale) const {
    return { getX() * scale, getY() * scale};
}

Resolution Resolution::operator*(double scale) const {
    return (scale >= 0) ? Resolution(static_cast<unsigned int>(getX() * scale), static_cast<unsigned int>(getY() * scale)) : Resolution(0,0);
}