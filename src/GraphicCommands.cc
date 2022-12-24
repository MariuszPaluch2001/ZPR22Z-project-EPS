//
// Created by kacper on 05.11.2022.
//
#include <sstream>


#include "GraphicCommands.h"


const double MAX_DIFFERENCE = 1e10;

std::string LeftOrientedLineCommand::toString() const {
  std::stringstream s;
  s << getMovePoint().getX() << " " << getMovePoint().getY() << " lineto";
  return s.str();
}

std::string RightOrientedLineCommand::toString() const {
  std::stringstream s;
  s << getMovePoint().getX() << " " << getMovePoint().getY() << " l";
  return s.str();
}

std::string PointCommand::toString() const {
  std::stringstream s;
  s << getMovePoint().getX() << " " << getMovePoint().getY()
    << " 1 1 r p2";
  return s.str();
}

std::string MoveCommand::toString() const {
    ///@todo implement
    return "";
}


double LeftOrientedLineCommand::countDifference(const LeftOrientedLineCommand & ll) const {
     return countDistanceBetweenConjoinedDirections(getMovePoint(), ll.getMovePoint());
}

double LeftOrientedLineCommand::countDifference(const RightOrientedLineCommand &) const {
    return MAX_DIFFERENCE;
}

double RightOrientedLineCommand::countDifference(const LeftOrientedLineCommand &) const {
    return MAX_DIFFERENCE;
}

double RightOrientedLineCommand::countDifference(const RightOrientedLineCommand & rl) const {
    return countDistanceBetweenConjoinedDirections(getMovePoint(), rl.getMovePoint());
}

RelativeCommand::VisitingVar LeftOrientedLineCommand::createMidpoint(const LeftOrientedLineCommand & ll) const {
    return LeftOrientedLineCommand(getMovePoint() + ll.getMovePoint());
}

RelativeCommand::VisitingVar LeftOrientedLineCommand::createMidpoint(const RightOrientedLineCommand &) const {
    return *this;
}

RelativeCommand::VisitingVar RightOrientedLineCommand::createMidpoint(const LeftOrientedLineCommand &) const {
    return *this;
}

RelativeCommand::VisitingVar RightOrientedLineCommand::createMidpoint(const RightOrientedLineCommand & rl) const {
    return RightOrientedLineCommand(getMovePoint() + rl.getMovePoint());
}

double PointCommand::countDifference(const PointCommand & p) const {
    return length(getMovePoint() - p.getMovePoint());
}

double PointCommand::countDifference(const MoveCommand & m) const {
    return length(getMovePoint() - m.getMovePoint());
}

double MoveCommand::countDifference(const PointCommand &) const {
    return 0;
}

double MoveCommand::countDifference(const MoveCommand &) const {
    return 0;
}

AbsoluteCommand::VisitingVar PointCommand::createMidpoint(const PointCommand & p) const {
    return PointCommand(p.getMovePoint());
}

AbsoluteCommand::VisitingVar PointCommand::createMidpoint(const MoveCommand & m) const {
    return PointCommand(m.getMovePoint());
}

AbsoluteCommand::VisitingVar MoveCommand::createMidpoint(const PointCommand & p) const {
    return p;
}

AbsoluteCommand::VisitingVar MoveCommand::createMidpoint(const MoveCommand & m) const {
    return m;
}