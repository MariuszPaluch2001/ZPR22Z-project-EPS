//
// Created by kacper on 06.11.2022.
//
#include "DifferenceVisitor.h"

//@todo - better logic is needed
const double DifferenceVisitor::MAX_DIFFERENCE = 1e10;

void DifferenceLeftLineVisitor::visit(const LeftOrientedLineCommand &ll) {
  DifferenceVisitor::setValue(countDistanceBetweenConjoinedDirections(ll_.getDirection(),
                                                   ll.getDirection()));
}

void DifferenceLeftLineVisitor::visit(const RightOrientedLineCommand &rl) {
    DifferenceVisitor::setValue(MAX_DIFFERENCE);

}

void DifferenceLeftLineVisitor::visit(const PointCommand &p) {
    DifferenceVisitor::setValue(length(ll_.getMovePoint() - p.getMovePoint()));
}

void DifferenceRightLineVisitor::visit(const LeftOrientedLineCommand &ll) {
  DifferenceVisitor::setValue(MAX_DIFFERENCE);
}

void DifferenceRightLineVisitor::visit(const RightOrientedLineCommand &rl) {
    DifferenceVisitor::setValue(countDistanceBetweenConjoinedDirections(rl_.getDirection(),
                                                   rl.getDirection()));
}

void DifferenceRightLineVisitor::visit(const PointCommand &p) {
  DifferenceVisitor::setValue(length(rl_.getMovePoint() - p.getMovePoint()));
}

void DifferencePointVisitor::visit(const LeftOrientedLineCommand &ll) {
  DifferenceVisitor::setValue(0);
}

void DifferencePointVisitor::visit(const RightOrientedLineCommand &rl) {
  DifferenceVisitor::setValue(0);
}

void DifferencePointVisitor::visit(const PointCommand &p) {
    DifferenceVisitor::setValue(length(p_.getMovePoint() - p.getMovePoint()));
}
