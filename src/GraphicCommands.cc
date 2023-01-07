//
// Created by kacper on 05.11.2022.
//
#include <sstream>


#include "GraphicCommands.h"


const double MAX_DIFFERENCE = 1e10;

std::string LeftLineCommand::toString() const {
  std::stringstream s;
  s << getMovePoint().getX() << " " << getMovePoint().getY() << " lineto";
  return s.str();
}

std::string RightLineCommand::toString() const {
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
    std::stringstream s;
    s << getMovePoint().getX() << " " << getMovePoint().getY()
      << " m";
    return s.str();
}

double countDifference(const LeftLineCommand & ll1, const LeftLineCommand & ll2) {
    return countDistanceBetweenConjoinedDirections(ll1.getMovePoint(), ll2.getMovePoint());
}

double countDifference(const LeftLineCommand & ll1, const RightLineCommand & rl2) {
    return MAX_DIFFERENCE;

}

double countDifference(const RightLineCommand & rl1, const LeftLineCommand & ll2) {
    return MAX_DIFFERENCE;
}


double countDifference(const RightLineCommand & rl1, const RightLineCommand & rl2) {
    return countDistanceBetweenConjoinedDirections(rl1.getMovePoint(), rl2.getMovePoint());

}

double countDifference(const PointCommand & p1, const PointCommand & p2) {
    return length(p1.getMovePoint() - p2.getMovePoint());
}
double countDifference(const PointCommand & p1, const MoveCommand & m2) {
    return length(p1.getMovePoint() - m2.getMovePoint());
}

double countDifference(const MoveCommand & m1, const PointCommand & p2) {
    return 0;
}
double countDifference(const MoveCommand & m1, const MoveCommand & m2) {
    return 0;
}

RelativeCommandVar createMidpoint(const LeftLineCommand & ll1, const LeftLineCommand & ll2) {
    return LeftLineCommand(ll1.getMovePoint() + ll2.getMovePoint());
}
RelativeCommandVar createMidpoint(const LeftLineCommand & ll1, const RightLineCommand & rl2) {
    return ll1;
}
RelativeCommandVar createMidpoint(const RightLineCommand & rl1, const LeftLineCommand & ll2) {
    return rl1;
}
RelativeCommandVar createMidpoint(const RightLineCommand & rl1, const RightLineCommand & rl2) {
    return RightLineCommand(rl1.getMovePoint() + rl2.getMovePoint());
}

AbsoluteCommandVar createMidpoint(const PointCommand & p1, const PointCommand & p2) {
    return p2;
}
AbsoluteCommandVar createMidpoint(const PointCommand & p1, const MoveCommand & m2) {
    return PointCommand(m2.getMovePoint());
}
AbsoluteCommandVar createMidpoint(const MoveCommand & m1, const PointCommand & p2) {
    return p2;
}
AbsoluteCommandVar createMidpoint(const MoveCommand & m1, const MoveCommand & m2) {
    return m2;
}