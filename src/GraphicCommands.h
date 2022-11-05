//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_GRAPHICCOMMANDS_H
#define ZPR_GRAPHICCOMMANDS_H
#include "EPSCommandRepresentation.h"
#include <memory>
class DifferenceVisitor;
class GraphicCommand : public Command {
    Point startingPoint;
    //represents point, to which drawing cursor is moved after the command
    Point movePoint;
public:
    GraphicCommand( const Point & start, const Point & move ) : startingPoint( start ), movePoint( move ) {}
    Point getStartingPoint() const { return startingPoint; }
    Point getMovePoint() const { return movePoint; }
    virtual std::string toString() const = 0;
    virtual double acceptDifferenceVisitor( const DifferenceVisitor & v ) const = 0;
    virtual double countDifference( const GraphicCommand & gc ) = 0;

};

class LeftOrientedLineCommand : public GraphicCommand {

    LeftOrientedLineCommand(const Point &start, const Point &move) : GraphicCommand(start, move) {}
    virtual std::string toString() const { /* @todo implement*/ return ""; }
    virtual double acceptDifferenceVisitor( const DifferenceVisitor & v ) const;
    virtual double countDifference(const GraphicCommand &gc) {}
};

class RightOrientedLineCommand : public GraphicCommand {
    RightOrientedLineCommand( const Point & start, const Point & move ) : GraphicCommand( start, move ) {}
    virtual std::string toString() const { /* @todo implement*/ return ""; }
    virtual double acceptDifferenceVisitor( const DifferenceVisitor & v ) const;
    virtual double countDifference(const GraphicCommand &gc) {}
};

class PointCommand: public GraphicCommand {
    PointCommand( const Point & coord ) : GraphicCommand( coord, coord ) {}
    virtual std::string toString() const { /* @todo implement*/ return ""; }
    virtual double acceptDifferenceVisitor( const DifferenceVisitor & v ) const;
    virtual double countDifference(const GraphicCommand &gc) {}
};

class DifferenceVisitor {
public:
    virtual ~DifferenceVisitor() = default;
    virtual double visit( const LeftOrientedLineCommand & ll ) const = 0;
    virtual double visit( const RightOrientedLineCommand & rl ) const = 0;
    virtual double visit( const PointCommand & p ) const = 0;
};


class LeftLineDifferenceVisitor : public DifferenceVisitor {
    const LeftOrientedLineCommand & ll_;
public:
    LeftLineDifferenceVisitor(const LeftOrientedLineCommand & ll ) : ll_( ll ) {}
    virtual double visit( const LeftOrientedLineCommand & ll ) const { /* @todo implement*/ return 0; }
    virtual double visit( const RightOrientedLineCommand & rl ) const { /* @todo implement*/ return 0; }
    virtual double visit( const PointCommand & p ) const { /* @todo implement*/ return 0; }
};

class RightLineDifferenceVisitor : public DifferenceVisitor {
    const RightOrientedLineCommand & rl_;
public:
    RightLineDifferenceVisitor(const RightOrientedLineCommand & rl ) : rl_( rl ) {}
    virtual double visit( const LeftOrientedLineCommand & ll ) const { /* @todo implement*/ return 0; }
    virtual double visit( const RightOrientedLineCommand & rl ) const { /* @todo implement*/ return 0; }
    virtual double visit( const PointCommand & p ) const { /* @todo implement*/ return 0; }
};

class PointDifferenceVisitor : public DifferenceVisitor {
    const PointCommand & p_;
public:
    PointDifferenceVisitor(const PointCommand & p ) : p_( p ) {}
    virtual double visit( const LeftOrientedLineCommand & ll ) const { /* @todo implement*/ return 0; }
    virtual double visit( const RightOrientedLineCommand & rl ) const { /* @todo implement*/ return 0; }
    virtual double visit( const PointCommand & p ) const { /* @todo implement*/ return 0; }
};

#endif //ZPR_GRAPHICCOMMANDS_H
