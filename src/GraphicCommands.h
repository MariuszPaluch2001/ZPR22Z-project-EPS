//
// Created by kacper on 04.11.2022.
// File contains classes representing Processable Graphic Commands - the ones
// which we will try to compress
//

#ifndef ZPR_GRAPHICCOMMANDS_H
#define ZPR_GRAPHICCOMMANDS_H
#include "EPSCommandRepresentation.h"
#include <optional>
#include <variant>

class GraphicCommand;
class LeftOrientedLineCommand;
class RightOrientedLineCommand;
class PointCommand;

using VarGraphic = std::variant<LeftOrientedLineCommand,
                                RightOrientedLineCommand, PointCommand>;
using OptGraphic = std::optional<VarGraphic>;
class Visitor;

class GraphicCommand : public Command {
  // represents Coordinates, to which drawing cursor is moved after the command
  Coordinates move_point_;

public:
  GraphicCommand(const Coordinates &move) : move_point_(move) {}
  Coordinates getMovePoint() const { return move_point_; }
  virtual std::string toString() const = 0;
  virtual void accept(Visitor &v) const = 0;

  virtual double countDifference(const GraphicCommand &gc) const = 0;
  virtual OptGraphic createMidpoint(const GraphicCommand &gc) const = 0;
};

//@todo maybe add abstract class for Line?
class LeftOrientedLineCommand : public GraphicCommand {
public:
  LeftOrientedLineCommand(const Coordinates &move) : GraphicCommand(move) {}
  virtual std::string toString() const;
  virtual void accept(Visitor &v) const;
  virtual double countDifference(const GraphicCommand &gc) const;
  virtual OptGraphic createMidpoint(const GraphicCommand &gc) const;
  Direction getDirection() const { return getMovePoint() - Coordinates(0, 0); }
};

class RightOrientedLineCommand : public GraphicCommand {
public:
  RightOrientedLineCommand(const Coordinates &move) : GraphicCommand(move) {}
  virtual std::string toString() const;
  virtual void accept(Visitor &v) const;
  virtual double countDifference(const GraphicCommand &gc) const;
  virtual OptGraphic createMidpoint(const GraphicCommand &gc) const;
  Direction getDirection() const { return getMovePoint() - Coordinates(0, 0); }
};

class PointCommand : public GraphicCommand {
public:
  PointCommand(const Coordinates &coord) : GraphicCommand(coord) {}
  virtual std::string toString() const;
  virtual void accept(Visitor &v) const;
  virtual double countDifference(const GraphicCommand &gc) const;
  virtual OptGraphic createMidpoint(const GraphicCommand &gc) const;
};

#endif // ZPR_GRAPHICCOMMANDS_H
