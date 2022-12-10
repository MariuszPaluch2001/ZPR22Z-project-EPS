//
// Created by kacper on 06.11.2022.
//
#include "DifferenceVisitor.h"

//@todo - better logic is needed
extern const double MAX_DIFFERENCE = 1e10;
void DifferenceLeftLineVisitor::visit(const LeftOrientedLineCommand &ll) {
  value_ = countDistanceBetweenConjoinedDirections(ll_.getDirection(),
                                                   ll.getDirection());
}

void DifferenceLeftLineVisitor::visit(const RightOrientedLineCommand &rl) {
  value_ = MAX_DIFFERENCE;
}

void DifferenceLeftLineVisitor::visit(const PointCommand &p) {
  value_ = length(ll_.getMovePoint() - p.getMovePoint());
}

void DifferenceRightLineVisitor::visit(const LeftOrientedLineCommand &ll) {
  value_ = MAX_DIFFERENCE;
}

void DifferenceRightLineVisitor::visit(const RightOrientedLineCommand &rl) {
  value_ = countDistanceBetweenConjoinedDirections(rl_.getDirection(),
                                                   rl.getDirection());
}

void DifferenceRightLineVisitor::visit(const PointCommand &p) {
  value_ = length(rl_.getMovePoint() - p.getMovePoint());
}

void DifferencePointVisitor::visit(const LeftOrientedLineCommand &ll) {
  value_ = 0;
}

void DifferencePointVisitor::visit(const RightOrientedLineCommand &rl) {
  value_ = 0;
}

void DifferencePointVisitor::visit(const PointCommand &p) {
  value_ = length(p_.getMovePoint() - p.getMovePoint());
}
