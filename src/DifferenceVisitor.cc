//
// Created by kacper on 06.11.2022.
//
#include "DifferenceVisitor.h"

const double MAX_DIFFERENCE = 1e10;

void DifferenceLeftLineVisitor::visit(const LeftOrientedLineCommand &ll) {
  DifferenceCarrier::setValue(countDistanceBetweenConjoinedDirections(
      ll_.getMovePoint(), ll.getMovePoint()));
}

void DifferenceLeftLineVisitor::visit(const RightOrientedLineCommand &rl) {
  DifferenceCarrier::setValue(MAX_DIFFERENCE);
}

void DifferenceLeftLineVisitor::visit(const PointCommand &p) {
  DifferenceCarrier::setValue(length(p.getMovePoint()));
}

void DifferenceRightLineVisitor::visit(const LeftOrientedLineCommand &ll) {
  DifferenceCarrier::setValue(MAX_DIFFERENCE);
}

void DifferenceRightLineVisitor::visit(const RightOrientedLineCommand &rl) {
  DifferenceCarrier::setValue(countDistanceBetweenConjoinedDirections(
      rl_.getMovePoint(), rl.getMovePoint()));
}

void DifferenceRightLineVisitor::visit(const PointCommand &p) {
  DifferenceCarrier::setValue(length(rl_.getMovePoint() - p.getMovePoint()));
}

void DifferencePointVisitor::visit(const LeftOrientedLineCommand &ll) {
  DifferenceCarrier::setValue(MAX_DIFFERENCE);
}

void DifferencePointVisitor::visit(const RightOrientedLineCommand &rl) {
  DifferenceCarrier::setValue(MAX_DIFFERENCE);
}

void DifferencePointVisitor::visit(const PointCommand &p) {
  DifferenceCarrier::setValue(length(p.getMovePoint()));
}
