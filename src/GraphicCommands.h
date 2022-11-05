//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_GRAPHICCOMMANDS_H
#define ZPR_GRAPHICCOMMANDS_H
#include "EPSCommandRepresentation.h"
#include <memory>

class Visitor;
class GraphicCommand : public Command {
    Point startingPoint;
    //represents point, to which drawing cursor is moved after the command
    Point movePoint;
public:
    GraphicCommand( const Point & start, const Point & move ) : startingPoint( start ), movePoint( move ) {}
    Point getStartingPoint() const { return startingPoint; }
    Point getMovePoint() const { return movePoint; }
    virtual std::string toString() const = 0;
    virtual double accept( const Visitor & dv );
};

class LeftOrientedLineCommand : public GraphicCommand {

    LeftOrientedLineCommand( const Point & start, const Point & move ) : GraphicCommand( start, move ) {}
};

class RightOrientedLineCommand : public GraphicCommand {
    RightOrientedLineCommand( const Point & start, const Point & move ) : GraphicCommand( start, move ) {}
};

class PointCommand: public GraphicCommand {
    PointCommand( const Point & coord ) : GraphicCommand( coord, coord ) {}
};



#endif //ZPR_GRAPHICCOMMANDS_H
