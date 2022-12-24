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

class RescalableCommand : public Command {
    Coordinates move_point_;
public:
    RescalableCommand(const Coordinates &move) : move_point_(move) {}
    Coordinates getMovePoint() const { return move_point_; }
    virtual std::string toString() const = 0;
    void rescale(double factor) { move_point_ = move_point_ * factor; }

};


class MoveCommand : public RescalableCommand {
    MoveCommand(const Coordinates &move) : RescalableCommand(move) {}
    virtual std::string toString() const { /* implement */ return ""; }
};

std::ostream &operator<<(std::ostream &os, const Command &com);

/*
 * Command that is not Left Line, Right Line or Point
 */
class NonProcessableCommand : public Command {
  std::string text_representation_;

public:
  NonProcessableCommand(const std::string &s) : text_representation_(s) {}
  virtual std::string toString() const override { return text_representation_; }
};


#endif // ZPR_EPSCOMMANDREPRESENTATION_H
