//
// Created by kacper on 04.11.2022.
// File contains base class for representation of EPS Commands
//

#ifndef ZPR_EPSCOMMANDREPRESENTATION_H
#define ZPR_EPSCOMMANDREPRESENTATION_H
#include "Scalar2DRepresentation.h"
#include <iostream>
/**
 * Klasa reprezentuje komendę EPS
 */
class Command {
public:
  virtual std::string toString() const = 0;
  virtual ~Command() = default;
};
/**
 * Klasa reprezentuje procesowalną komendę EPS
 */
class ProcessableCommand : public Command {
  CoordinateValue move_point_;

public:
  ProcessableCommand(const CoordinateValue &move) : move_point_(move) {}
  virtual std::string toString() const override = 0;
  /**
   * zwraca punkt, do którego przesuwa się kursor po narysowaniu komendy
   */
  CoordinateValue getMovePoint() const { return move_point_; }
  /**
   * pozwala na przeskalowanie komendy o zadany czynnik, przy pomniejszaniu
   * obrazka
   */
  void rescale(double factor) { move_point_ = move_point_ * factor; }
};

std::ostream &operator<<(std::ostream &os, const Command &com);

/**
 * Komenda, której nie poddajemy obróbce - trzymamy tylko jej reprezentację
 * tekstową
 */
class NonProcessableCommand : public Command {
  std::string text_representation_;

public:
  NonProcessableCommand(const std::string &s) : text_representation_(s) {}
  virtual std::string toString() const override { return text_representation_; }
};

#endif // ZPR_EPSCOMMANDREPRESENTATION_H
