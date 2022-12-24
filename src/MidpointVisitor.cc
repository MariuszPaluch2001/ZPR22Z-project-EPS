//
// Created by kacper on 06.11.2022.
//
#include "MidpointVisitor.h"

void MidpointLeftLineVisitor::visit(const LeftOrientedLineCommand &ll) {
    auto midpoint = LeftOrientedLineCommand(ll_.getMovePoint() + ll.getMovePoint());
    MidpointCarrier::setValue(midpoint);
}

void MidpointLeftLineVisitor::visit(const RightOrientedLineCommand &rl) {
    //do nothing
}

void MidpointLeftLineVisitor::visit(const PointCommand &p) {
    auto midpoint = LeftOrientedLineCommand(ll_.getMovePoint() + p.getMovePoint());
    MidpointCarrier::setValue(midpoint);
}

void MidpointRightLineVisitor::visit(const LeftOrientedLineCommand &rl) {
    //do nothing
}

void MidpointRightLineVisitor::visit(const RightOrientedLineCommand &rl) {

    auto midpoint = RightOrientedLineCommand(rl_.getMovePoint() + rl.getMovePoint());
    MidpointCarrier::setValue(midpoint);

}

void MidpointRightLineVisitor::visit(const PointCommand &p) {
    auto midpoint = RightOrientedLineCommand(rl_.getMovePoint() + p.getMovePoint());
    MidpointCarrier::setValue(midpoint);
}

void MidpointPointVisitor::visit(const LeftOrientedLineCommand &ll) {
    // do nothing
}

void MidpointPointVisitor::visit(const RightOrientedLineCommand &ll) {
    // do nothing
}

void MidpointPointVisitor::visit(const PointCommand &p) {
    auto midpoint = PointCommand(p_.getMovePoint() + p.getMovePoint());
    MidpointCarrier::setValue(midpoint);
}
