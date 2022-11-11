//
// Created by kacper on 06.11.2022.
//
#include "Visitor.h"
//@todo - better logic is needed
// and if not - we can change it to way simpler versions
template<> double LeftLineDifferenceVisitor::visit( const LeftOrientedLineCommand & ll ) const {
    return countDistanceBetweenConjoinedDirections( ll_.getDirection(), ll.getDirection() );
}

template<> double LeftLineDifferenceVisitor::visit( const RightOrientedLineCommand & rl ) const {
    //@todo change this
    return -1;
}

template<> double LeftLineDifferenceVisitor::visit( const PointCommand &p ) const {
    return length(ll_.getMovePoint() - p.getMovePoint());
}


template<> double RightLineDifferenceVisitor::visit( const LeftOrientedLineCommand & ll ) const {
    //@todo change this
    return -1;
}

template<> double RightLineDifferenceVisitor::visit( const RightOrientedLineCommand & rl ) const {
    return countDistanceBetweenConjoinedDirections( rl_.getDirection(), rl.getDirection() );
}

template<> double RightLineDifferenceVisitor::visit( const PointCommand &p ) const {
    return length(rl_.getMovePoint() - p.getMovePoint());
}

template<> double PointDifferenceVisitor::visit( const LeftOrientedLineCommand & ll ) const {
    return 0;
}

template<> double PointDifferenceVisitor::visit( const RightOrientedLineCommand & rl ) const {
    return 0;
}

template<> double PointDifferenceVisitor::visit( const PointCommand &p ) const {
    return length(p_.getMovePoint() - p.getMovePoint());
}