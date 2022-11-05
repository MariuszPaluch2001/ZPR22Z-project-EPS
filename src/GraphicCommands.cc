//
// Created by kacper on 05.11.2022.
//

#include "GraphicCommands.h"
#include "DifferenceVisitor.h"

double LeftOrientedLineCommand::acceptDifferenceVisitor( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double RightOrientedLineCommand::acceptDifferenceVisitor( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double PointCommand::acceptDifferenceVisitor( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double LeftOrientedLineCommand::countDifference(const GraphicCommand &gc) {
    auto visitor = LeftLineDifferenceVisitor(*this);
    return gc.acceptDifferenceVisitor(visitor);
}

double RightOrientedLineCommand::countDifference(const GraphicCommand &gc) {
    auto visitor = RightLineDifferenceVisitor(*this);
    return gc.acceptDifferenceVisitor(visitor);
}

double PointCommand::countDifference(const GraphicCommand &gc) {
    auto visitor = PointDifferenceVisitor(*this);
    return gc.acceptDifferenceVisitor(visitor);
}
