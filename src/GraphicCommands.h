//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_GRAPHICCOMMANDS_H
#define ZPR_GRAPHICCOMMANDS_H
#include "EPSCommandRepresentation.h"
#include <memory>

class GraphicCommand : public Command {
    Point startingPoint;
    //represents point, to which drawing cursor is moved after the command
    Point movePoint;
public:
    GraphicCommand( const Point & start, const Point & move ) : startingPoint( start ), movePoint( move ) {}
    Point getStartingPoint() const { return startingPoint; }
    Point getMovePoint() const { return movePoint; }
    virtual std::string toString() const = 0;
    virtual double difference(const GraphicCommand & com) const = 0;
    // creates Graphic Command that represents midpoint between two other commands
    virtual std::unique_ptr<GraphicCommand> createMidpoint( const GraphicCommand & com ) const = 0;
};
#endif //ZPR_GRAPHICCOMMANDS_H
