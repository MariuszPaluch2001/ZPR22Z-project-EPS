//
// Created by kacper on 05.11.2022.
//

#include "GraphicCommands.h"
#include "Visitor.h"

double LeftOrientedLineCommand::accept( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double RightOrientedLineCommand::accept( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double PointCommand::accept( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double LeftOrientedLineCommand::countDifference(const GraphicCommand &gc) {
    auto visitor = LeftLineDifferenceVisitor(*this);
    return gc.accept(visitor);
}

double RightOrientedLineCommand::countDifference(const GraphicCommand &gc) {
    auto visitor = RightLineDifferenceVisitor(*this);
    return gc.accept(visitor);
}

double PointCommand::countDifference(const GraphicCommand &gc) {
    auto visitor = PointDifferenceVisitor(*this);
    return gc.accept(visitor);
}
