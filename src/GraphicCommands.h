//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_GRAPHICCOMMANDS_H
#define ZPR_GRAPHICCOMMANDS_H
#include "EPSCommandRepresentation.h"
#include <memory>
#include <variant>
#include <optional>

class GraphicCommand;
class LeftOrientedLineCommand;
class RightOrientedLineCommand;
class PointCommand;

using varGraphic = std::variant<std::monostate, LeftOrientedLineCommand, RightOrientedLineCommand, PointCommand>;
class Visitor;
class DifferenceVisitor;
class MidpointVisitor;

class GraphicCommand : public Command {
    //represents point, to which drawing cursor is moved after the command
    Point movePoint;
public:
    GraphicCommand( const Point & move ) : movePoint( move ) {}
    Point getMovePoint() const { return movePoint; }
    virtual std::string toString() const = 0;
    virtual void accept(Visitor & v) const = 0;

    virtual double countDifference( const GraphicCommand & gc ) const = 0;
    virtual varGraphic createMidpoint( const GraphicCommand & gc ) const = 0;

};

//@todo maybe add abstract class for Line?
class LeftOrientedLineCommand : public GraphicCommand {
public:
    LeftOrientedLineCommand(const Point &move) : GraphicCommand(move) {}
    virtual std::string toString() const { return ""; /* @todo implement*/ }
    virtual void accept(Visitor & v) const;
    virtual double countDifference(const GraphicCommand &gc) const;
    virtual varGraphic createMidpoint( const GraphicCommand & gc ) const;
    //@todo - make it better
    Direction getDirection() const { return getMovePoint() - Point(0,0); }
};

class RightOrientedLineCommand : public GraphicCommand {
public:
    RightOrientedLineCommand( const Point & move ) : GraphicCommand( move ) {}
    virtual std::string toString() const { return "";/* @todo implement*/  }
    virtual void accept(Visitor & v) const;
    virtual double countDifference(const GraphicCommand &gc) const;
    virtual varGraphic createMidpoint( const GraphicCommand & gc ) const;
    //@todo - make it better
    Direction getDirection() const { return getMovePoint() - Point(0,0); }
};

class PointCommand: public GraphicCommand {
public:
    PointCommand( const Point & coord ) : GraphicCommand( coord ) {}
    virtual std::string toString() const { return "";/* @todo implement*/  }
    virtual void accept(Visitor & v) const;
    virtual double countDifference(const GraphicCommand &gc) const;
    virtual varGraphic createMidpoint( const GraphicCommand & gc ) const;
};



#endif //ZPR_GRAPHICCOMMANDS_H