//
// Created by kacper on 05.11.2022.
//

#include "GraphicCommands.h"
#include "Visitor.h"
#include <sstream>

std::string LeftOrientedLineCommand::toString() const {
    std::stringstream s;
    s << "LeftOrientedLine: ";
    s << "Start (" << getStartingPoint().getX() << ", " << getStartingPoint().getX()  << ") ";
    s << "Move (" << getMovePoint().getX() << ", " << getMovePoint().getX()  << ")";
    return s.str();
}

std::string RightOrientedLineCommand::toString() const {
    std::stringstream s;
    s << "RightOrientedLine: ";
    s << "Start (" << getStartingPoint().getX() << ", " << getStartingPoint().getX()  << ") ";
    s << "Move (" << getMovePoint().getX() << ", " << getMovePoint().getX()  << ")";
    return s.str();
}

std::string PointCommand::toString() const {
    std::stringstream s;
    s << "PointCommand: ";
    s << "Start (" << getStartingPoint().getX() << ", " << getStartingPoint().getX()  << ") ";
    s << "Move (" << getMovePoint().getX() << ", " << getMovePoint().getX()  << ")";    return s.str();
}

double LeftOrientedLineCommand::accept( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double RightOrientedLineCommand::accept( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double PointCommand::accept( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double LeftOrientedLineCommand::countDifference(const GraphicCommand &gc) {
    auto visitor = LeftLineDifferenceVisitor(*this);
    return gc.accept(visitor);
}

double RightOrientedLineCommand::countDifference(const GraphicCommand &gc) {
    auto visitor = RightLineDifferenceVisitor(*this);
    return gc.accept(visitor);
}

double PointCommand::countDifference(const GraphicCommand &gc) {
    auto visitor = PointDifferenceVisitor(*this);
    return gc.accept(visitor);
}
