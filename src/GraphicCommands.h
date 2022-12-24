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
class Visitor;

class GraphicCommand : public RescalableCommand {
  // represents Coordinates, to which drawing cursor is moved after the command

public:
  GraphicCommand(const Direction &move) : RescalableCommand(move) {}
  virtual std::string toString() const = 0;
  virtual void accept(Visitor &v) const = 0;

  virtual double countDifference(const GraphicCommand &gc) const = 0;
  virtual VarGraphic createMidpoint(const GraphicCommand &gc) const = 0;


};

class LeftOrientedLineCommand : public GraphicCommand {
public:
  LeftOrientedLineCommand(const Direction &move) : GraphicCommand(move) {}
  virtual std::string toString() const override;
  virtual void accept(Visitor &v) const override;
  virtual double countDifference(const GraphicCommand &gc) const override;
  virtual VarGraphic createMidpoint(const GraphicCommand &gc) const override;
};

class RightOrientedLineCommand : public GraphicCommand {
public:
  RightOrientedLineCommand(const Direction &move) : GraphicCommand(move) {}
  virtual std::string toString() const override;
  virtual void accept(Visitor &v) const override;
  virtual double countDifference(const GraphicCommand &gc) const override;
  virtual VarGraphic createMidpoint(const GraphicCommand &gc) const override;
};

class PointCommand : public GraphicCommand {
public:
  PointCommand(const CoordinateValue &coord) : GraphicCommand(coord) {}
  virtual std::string toString() const override;
  virtual void accept(Visitor &v) const override;
  virtual double countDifference(const GraphicCommand &gc) const override;
  virtual VarGraphic createMidpoint(const GraphicCommand &gc) const override;
};

#endif // ZPR_GRAPHICCOMMANDS_H
