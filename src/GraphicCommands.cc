//
// Created by kacper on 05.11.2022.
//

#include "GraphicCommands.h"


double LeftOrientedLineCommand::acceptDifferenceVisitor( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double RightOrientedLineCommand::acceptDifferenceVisitor( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

double PointCommand::acceptDifferenceVisitor( const DifferenceVisitor & v ) const {
    return v.visit(*this);
}

