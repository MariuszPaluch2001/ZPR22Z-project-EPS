//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_GRAPHICCOMMANDS_H
#define ZPR_GRAPHICCOMMANDS_H
#include "EPSCommandRepresentation.h"
#include <memory>

class GraphicCommand;
template <typename T /* return value of visitor */> class Visitor;
using MidpointVisitor = Visitor<std::unique_ptr<GraphicCommand>>;
using DifferenceVisitor = Visitor<double>;

class GraphicCommand : public Command {
    Point startingPoint;
    //represents point, to which drawing cursor is moved after the command
    Point movePoint;
public:
    GraphicCommand( const Point & start, const Point & move ) : startingPoint( start ), movePoint( move ) {}
    Point getStartingPoint() const { return startingPoint; }
    Point getMovePoint() const { return movePoint; }
    virtual std::string toString() const = 0;
    virtual double accept( const DifferenceVisitor & v) const = 0;

    virtual double countDifference( const GraphicCommand & gc ) = 0;

    virtual std::unique_ptr<GraphicCommand> accept( const MidpointVisitor & mv ) const = 0;
    virtual std::unique_ptr<GraphicCommand> createMidpoint( const GraphicCommand & gc ) const = 0;

};

class LeftOrientedLineCommand : public GraphicCommand {
public:
    LeftOrientedLineCommand(const Point &start, const Point &move) : GraphicCommand(start, move) {}
    virtual std::string toString() const { return "LeftOrientedLineCommand"; }
    virtual double accept( const DifferenceVisitor & v ) const;
    virtual double countDifference(const GraphicCommand &gc);
    virtual std::unique_ptr<GraphicCommand> accept( const MidpointVisitor & mv )  const {  }
    virtual std::unique_ptr<GraphicCommand> createMidpoint( const GraphicCommand & gc ) const { }
};

class RightOrientedLineCommand : public GraphicCommand {
public:
    RightOrientedLineCommand( const Point & start, const Point & move ) : GraphicCommand( start, move ) {}
    virtual std::string toString() const { return "RightOrientedLineCommand"; }
    virtual double accept( const DifferenceVisitor & v ) const;
    virtual double countDifference(const GraphicCommand &gc);
    virtual std::unique_ptr<GraphicCommand> accept( const MidpointVisitor & mv )   const {   }
    virtual std::unique_ptr<GraphicCommand> createMidpoint( const GraphicCommand & gc )   const  {   }
};

class PointCommand: public GraphicCommand {
public:
    PointCommand( const Point & coord ) : GraphicCommand( coord, coord ) {}
    virtual std::string toString() const { return "PointCommand"; }
    virtual double accept( const DifferenceVisitor & v ) const;
    virtual double countDifference(const GraphicCommand &gc);
    virtual std::unique_ptr<GraphicCommand> accept( const MidpointVisitor & mv ) const {   }
    virtual std::unique_ptr<GraphicCommand> createMidpoint( const GraphicCommand & gc ) const { }
};



#endif //ZPR_GRAPHICCOMMANDS_H
