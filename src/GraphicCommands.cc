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

double LeftOrientedLineCommand::countDifference(const GraphicCommand &gc) const {
    auto visitor = LeftLineDifferenceVisitor(*this);
    return gc.accept(visitor);
}

double RightOrientedLineCommand::countDifference(const GraphicCommand &gc) const {
    auto visitor = RightLineDifferenceVisitor(*this);
    return gc.accept(visitor);
}

double PointCommand::countDifference(const GraphicCommand &gc) const {
    auto visitor = PointDifferenceVisitor(*this);
    return gc.accept(visitor);
}

gcPtr LeftOrientedLineCommand::accept(const MidpointVisitor &mv) const {
    return mv.visit(*this);
}

gcPtr RightOrientedLineCommand::accept(const MidpointVisitor &mv) const {
    return mv.visit(*this);
}

gcPtr PointCommand::accept(const MidpointVisitor &mv) const {
    return mv.visit(*this);
}

gcPtr LeftOrientedLineCommand::createMidpoint(const GraphicCommand &gc) const {
    auto visitor = LeftLineMidpointVisitor(*this);
    return gc.accept(visitor);
}

gcPtr RightOrientedLineCommand::createMidpoint(const GraphicCommand &gc) const {
    auto visitor = RightLineMidpointVisitor(*this);
    return gc.accept(visitor);
}

gcPtr PointCommand::createMidpoint(const GraphicCommand &gc) const {
    auto visitor = PointMidpointVisitor(*this);
    return gc.accept(visitor);
}
