//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_GRAPHICCOMMANDS_H
#define ZPR_GRAPHICCOMMANDS_H
#include "EPSCommandRepresentation.h"
#include <memory>

class GraphicCommand;
using gcPtr = std::unique_ptr<GraphicCommand>;
template <typename T /* return value of visitor */> class Visitor;
using MidpointVisitor = Visitor<gcPtr>;
using DifferenceVisitor = Visitor<double>;

class GraphicCommand : public Command {
    //represents point, to which drawing cursor is moved after the command
    Point movePoint;
public:
    GraphicCommand( const Point & move ) : movePoint( move ) {}
    Point getMovePoint() const { return movePoint; }
    virtual std::string toString() const = 0;
    virtual double accept( const DifferenceVisitor & v) const = 0;

    virtual double countDifference( const GraphicCommand & gc ) const = 0;

    virtual gcPtr accept( const MidpointVisitor & mv ) const = 0;
    virtual gcPtr createMidpoint( const GraphicCommand & gc ) const = 0;

};

//@todo maybe add abstract class for Line?
class LeftOrientedLineCommand : public GraphicCommand {
public:
    LeftOrientedLineCommand(const Point &move) : GraphicCommand(move) {}
    virtual std::string toString() const { return ""; /* @todo implement*/ }
    virtual double accept( const DifferenceVisitor & v ) const;
    virtual double countDifference(const GraphicCommand &gc) const;
    virtual gcPtr accept( const MidpointVisitor & mv ) const;
    virtual gcPtr createMidpoint( const GraphicCommand & gc ) const;
    //@todo - make it better
    Direction getDirection() const { return getMovePoint() - Point(0,0); }
};

class RightOrientedLineCommand : public GraphicCommand {
public:
    RightOrientedLineCommand( const Point & move ) : GraphicCommand( move ) {}
    virtual std::string toString() const { return "";/* @todo implement*/  }
    virtual double accept( const DifferenceVisitor & v ) const;
    virtual double countDifference(const GraphicCommand &gc) const;
    virtual gcPtr accept( const MidpointVisitor & mv ) const;
    virtual gcPtr createMidpoint( const GraphicCommand & gc ) const;
    //@todo - make it better
    Direction getDirection() const { return getMovePoint() - Point(0,0); }
};

class PointCommand: public GraphicCommand {
public:
    PointCommand( const Point & coord ) : GraphicCommand( coord ) {}
    virtual std::string toString() const { return "";/* @todo implement*/  }
    virtual double accept( const DifferenceVisitor & v ) const;
    virtual double countDifference(const GraphicCommand &gc) const;
    virtual gcPtr accept( const MidpointVisitor & mv ) const;
    virtual gcPtr createMidpoint( const GraphicCommand & gc ) const;
};



#endif //ZPR_GRAPHICCOMMANDS_H
