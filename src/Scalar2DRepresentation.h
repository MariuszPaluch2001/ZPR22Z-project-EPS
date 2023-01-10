//
// Created by kacper on 04.11.2022.
// File contains classes representing entity from linear algebra having two
// values - (x,y)
//

#ifndef ZPR_SCALAR2DREPRESENTATION_H
#define ZPR_SCALAR2DREPRESENTATION_H
#include <iostream>
/**
 * Reprezentuje krotkę opisującą punkt/wektor w przestrzeni 2 wymiarowej
 */
class CoordinateValue {
  double x_, y_;

public:
  CoordinateValue(double x, double y) : x_(x), y_(y) {}
  std::string toString() const;
  double getX() const { return x_; }
  double getY() const { return y_; }
  void setX(double new_x) { x_ = new_x; }
  void setY(double new_y) { y_ = new_y; }
  /**
   * Dodaje 2 współrzędne do siebie - element po elemencie
   * @return dla (x1,y1) + (x2, y2) zwraca (x1+x2, y1+y2)
   */
  CoordinateValue operator+(const CoordinateValue &d) const;
  /**
   * Odejmuje 2 współrzędne od siebie - element po elemencie
   * @return dla (x1,y1) - (x2, y2) zwraca (x1-x2, y1-y2)
   */
  CoordinateValue operator-(const CoordinateValue &d) const;
  /**
   * Dzieli krotkę przez skalar - element po elemencie
   */
  CoordinateValue operator/(double div) const;
  /**
   * Mnoży krotkę przez skalar - element po elemencie
   */
  CoordinateValue operator*(double scale) const;
};

using Direction = CoordinateValue;
using Coordinates = CoordinateValue;
/**
 * Reprezentuje krotkę (x,y) opisującą rozdzielczość obrazka
 */
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
  /**
   * Mnoży krotkę przez skalar - element po elemencie
   */
  Resolution operator*(double scale) const;
};
std::ostream &operator<<(std::ostream &os, const Resolution &res);
std::ostream &operator<<(std::ostream &os, const CoordinateValue &cv);
/**
 * Zwraca długość wektora współrzędnych
 */
double length(const Direction &d);
/**
 * Zwraca wektor jednostkowy o tym samym kierunku, co wektor zadany
 */
Direction normalizeDirection(const Direction &d);

/**
 * Zwraca współrzędne kontowe w radianach
 */
double getDirectionAngle(const Direction &d);
/**
 * Funkcja liczy odległość między dwoma wektorami
 * @param d1 - wektor pierwszy
 * @param d2 - wektor drugi, zaczepiony na końcu wektora d1
 * jeżeli wektory nie są skierowane w przeciwne strony (kąt między kierunkami >
 * 90 albo < -90) zwraca 0 w przeciwnym przypadku dokonuje rzutu jednego wektora
 * na drugi - i zwraca wysokość rzutu
 */
double countDistanceBetweenConjoinedDirections(const Direction &d1,
                                               const Direction &d2);
#endif // ZPR_SCALAR2DREPRESENTATION_H
