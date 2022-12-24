//
// Created by kacper on 06.11.2022.
//
#include "MidpointVisitor.h"
//@todo change dummy implementations
void MidpointLeftLineVisitor::visit(const LeftOrientedLineCommand &ll) {
    MidpointCarrier::setValue(ll);
}

void MidpointLeftLineVisitor::visit(const RightOrientedLineCommand &rl) {
    //do nothing
}

void MidpointLeftLineVisitor::visit(const PointCommand &p) {
    MidpointCarrier::setValue(LeftOrientedLineCommand(p.getMovePoint()));
}

void MidpointRightLineVisitor::visit(const LeftOrientedLineCommand &rl) {
    //do nothing
}

void MidpointRightLineVisitor::visit(const RightOrientedLineCommand &rl) {
    MidpointCarrier::setValue(rl);
}

void MidpointRightLineVisitor::visit(const PointCommand &p) {
    MidpointCarrier::setValue(RightOrientedLineCommand(p.getMovePoint()));
}

void MidpointPointVisitor::visit(const LeftOrientedLineCommand &ll) {
    // do nothing
}

void MidpointPointVisitor::visit(const RightOrientedLineCommand &ll) {
    // do nothing
}

void MidpointPointVisitor::visit(const PointCommand &p) {
    MidpointCarrier::setValue(p);
}
