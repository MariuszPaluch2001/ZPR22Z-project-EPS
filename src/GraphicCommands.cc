//
// Created by kacper on 05.11.2022.
//

#include "GraphicCommands.h"
#include "DifferenceVisitor.h"
#include "MidpointVisitor.h"

void LeftOrientedLineCommand::accept(Visitor &v) const {
    v.visit(*this);
}

void RightOrientedLineCommand::accept(Visitor &v) const {
    v.visit(*this);
}

void PointCommand::accept(Visitor &v) const {
    v.visit(*this);
}

double LeftOrientedLineCommand::countDifference(const GraphicCommand &gc) const {
    auto visitor = DifferenceLeftLineVisitor(*this);
    gc.accept(visitor);
    return visitor.getValue();
}

double RightOrientedLineCommand::countDifference(const GraphicCommand &gc) const {
    auto visitor = DifferenceRightLineVisitor(*this);
    gc.accept(visitor);
    return visitor.getValue();
}

double PointCommand::countDifference(const GraphicCommand &gc) const {
    auto visitor = DifferencePointVisitor(*this);
    gc.accept(visitor);
    return visitor.getValue();
}

OptGraphic LeftOrientedLineCommand::createMidpoint(const GraphicCommand &gc) const {
    auto visitor = MidpointLeftLineVisitor(*this);
    gc.accept(visitor);
    return visitor.getValue();
}

OptGraphic RightOrientedLineCommand::createMidpoint(const GraphicCommand &gc) const {
    auto visitor = MidpointRightLineVisitor(*this);
    gc.accept(visitor);
    return visitor.getValue();
}

OptGraphic PointCommand::createMidpoint(const GraphicCommand &gc) const {
    auto visitor = MidpointPointVisitor(*this);
    gc.accept(visitor);
    return visitor.getValue();
}
