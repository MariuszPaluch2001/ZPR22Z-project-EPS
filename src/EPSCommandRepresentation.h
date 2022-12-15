//
// Created by kacper on 04.11.2022.
// File contains base class for representation of EPS Commands
//

#ifndef ZPR_EPSCOMMANDREPRESENTATION_H
#define ZPR_EPSCOMMANDREPRESENTATION_H
#include "Scalar2DRepresentation.h"
#include <iostream>

class Command {
public:
  virtual std::string toString() const = 0;
  virtual ~Command() = default;
};

std::ostream &operator<<(std::ostream &os, const Command &com);

/*
 * Command that is not Left Line, Right Line or Point
 */
class NonProcessableCommand : public Command {
  std::string text_representation_;

public:
  NonProcessableCommand(const std::string &s) : text_representation_(s) {}
  std::string toString() const { return text_representation_; }
};

#endif // ZPR_EPSCOMMANDREPRESENTATION_H
