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

class LeftOrientedLineCommand;
class RightOrientedLineCommand;
class PointCommand;
class MoveCommand;


template <typename VisitingType1, typename VisitingType2>
class GraphicCommand : public ProcessableCommand{
public:
    GraphicCommand(const CoordinateValue & cv) : ProcessableCommand(cv) {}
    virtual std::string toString() const override = 0;

    virtual double countDifference(const VisitingType1 & vt) const = 0;
    virtual double countDifference(const VisitingType2 &) const = 0;
    using VisitingVar = std::variant<VisitingType1, VisitingType2>;
    virtual VisitingVar createMidpoint(const VisitingType1 & vt) const = 0;
    virtual VisitingVar createMidpoint(const VisitingType2 & vt) const = 0;
};

using RelativeCommand = GraphicCommand<LeftOrientedLineCommand, RightOrientedLineCommand>;
using AbsoluteCommand = GraphicCommand<PointCommand, MoveCommand>;

class LeftOrientedLineCommand : public RelativeCommand {
public:
  LeftOrientedLineCommand(const Direction &move) : RelativeCommand(move) {}
  virtual std::string toString() const override;
  virtual double countDifference(const LeftOrientedLineCommand &) const override;
  virtual double countDifference(const RightOrientedLineCommand &) const override;

  virtual RelativeCommand::VisitingVar createMidpoint(const LeftOrientedLineCommand &) const override;
  virtual RelativeCommand::VisitingVar createMidpoint(const RightOrientedLineCommand &) const override;
};

class RightOrientedLineCommand : public RelativeCommand {
public:
    RightOrientedLineCommand(const Direction &move) : RelativeCommand(move) {}
    virtual std::string toString() const override;
    virtual double countDifference(const LeftOrientedLineCommand &) const override;
    virtual double countDifference(const RightOrientedLineCommand &) const override;

    virtual RelativeCommand::VisitingVar createMidpoint(const LeftOrientedLineCommand &) const override;
    virtual RelativeCommand::VisitingVar createMidpoint(const RightOrientedLineCommand &) const override;
};

class PointCommand : public AbsoluteCommand {
public:
  PointCommand(const Coordinates &coord) : AbsoluteCommand(coord) {}
    virtual std::string toString() const override;
    virtual double countDifference(const PointCommand &) const override;
    virtual double countDifference(const MoveCommand &) const override;

    virtual AbsoluteCommand::VisitingVar createMidpoint(const PointCommand &) const override;
    virtual AbsoluteCommand::VisitingVar createMidpoint(const MoveCommand &) const override;
};

class MoveCommand : public AbsoluteCommand {
public:
    MoveCommand(const Coordinates & coord) : AbsoluteCommand(coord) {}
    virtual std::string toString() const override;
    virtual double countDifference(const PointCommand &) const override;
    virtual double countDifference(const MoveCommand &) const override;

    virtual AbsoluteCommand::VisitingVar createMidpoint(const PointCommand &) const override;
    virtual AbsoluteCommand::VisitingVar createMidpoint(const MoveCommand &) const override;
};
#endif // ZPR_GRAPHICCOMMANDS_H
