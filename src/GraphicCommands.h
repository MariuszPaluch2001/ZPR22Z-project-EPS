//
// Created by kacper on 04.11.2022.
// File contains classes representing Processable Graphic Commands - the ones which we will try
// to compress
//

#ifndef ZPR_GRAPHICCOMMANDS_H
#define ZPR_GRAPHICCOMMANDS_H
#include <optional>
#include <variant>
#include "EPSCommandRepresentation.h"


class GraphicCommand;
class LeftOrientedLineCommand;
class RightOrientedLineCommand;
class PointCommand;

using VarGraphic = std::variant<LeftOrientedLineCommand,
                                RightOrientedLineCommand, PointCommand>;
using OptGraphic = std::optional<VarGraphic>;
class Visitor;

class GraphicCommand : public Command {
  // represents point, to which drawing cursor is moved after the command
  Point move_point_;

public:
  GraphicCommand(const Point &move) : move_point_(move) {}
  Point getMovePoint() const { return move_point_; }
  virtual std::string toString() const = 0;
  virtual void accept(Visitor &v) const = 0;

  virtual double countDifference(const GraphicCommand &gc) const = 0;
  virtual OptGraphic createMidpoint(const GraphicCommand &gc) const = 0;
};

//@todo maybe add abstract class for Line?
class LeftOrientedLineCommand : public GraphicCommand {
public:
  LeftOrientedLineCommand(const Point &move) : GraphicCommand(move) {}
  virtual std::string toString() const;
  virtual void accept(Visitor &v) const;
  virtual double countDifference(const GraphicCommand &gc) const;
  virtual OptGraphic createMidpoint(const GraphicCommand &gc) const;
  Direction getDirection() const { return getMovePoint() - Point(0, 0); }
};

class RightOrientedLineCommand : public GraphicCommand {
public:
  RightOrientedLineCommand(const Point &move) : GraphicCommand(move) {}
  virtual std::string toString() const;
  virtual void accept(Visitor &v) const;
  virtual double countDifference(const GraphicCommand &gc) const;
  virtual OptGraphic createMidpoint(const GraphicCommand &gc) const;
  Direction getDirection() const { return getMovePoint() - Point(0, 0); }
};

class PointCommand : public GraphicCommand {
public:
  PointCommand(const Point &coord) : GraphicCommand(coord) {}
  virtual std::string toString() const;
  virtual void accept(Visitor &v) const;
  virtual double countDifference(const GraphicCommand &gc) const;
  virtual OptGraphic createMidpoint(const GraphicCommand &gc) const;
};

#endif // ZPR_GRAPHICCOMMANDS_H
