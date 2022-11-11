//
// Created by kacper on 06.11.2022.
//
#include "Visitor.h"
//@todo better logic is needed
template<> gcPtr LeftLineMidpointVisitor::visit( const LeftOrientedLineCommand & ll ) const {
    return gcPtr(new LeftOrientedLineCommand(ll.getMovePoint()));
}

template<> gcPtr LeftLineMidpointVisitor::visit( const RightOrientedLineCommand & rl ) const {
    return gcPtr ( nullptr );
}

template<> gcPtr LeftLineMidpointVisitor::visit( const PointCommand &p ) const {
    return gcPtr(new LeftOrientedLineCommand(p.getMovePoint()));
}


template<> gcPtr RightLineMidpointVisitor::visit( const LeftOrientedLineCommand & ll ) const {
    return gcPtr( nullptr );
}

template<> gcPtr RightLineMidpointVisitor::visit( const RightOrientedLineCommand & rl ) const {
    return gcPtr (new RightOrientedLineCommand(rl_.getMovePoint()));
}

template<> gcPtr RightLineMidpointVisitor::visit( const PointCommand &p ) const {
    return gcPtr(new RightOrientedLineCommand(p.getMovePoint()));
}

template<> gcPtr PointMidpointVisitor::visit( const LeftOrientedLineCommand & ll ) const {
    return gcPtr ( new LeftOrientedLineCommand(ll.getMovePoint()));
}

template<> gcPtr PointMidpointVisitor::visit( const RightOrientedLineCommand & rl ) const {
    return gcPtr ( new RightOrientedLineCommand(rl.getMovePoint()));
}

template<> gcPtr PointMidpointVisitor::visit( const PointCommand &p ) const {
    auto coord1 = p_.getMovePoint();
    auto coord2 = p.getMovePoint();
    return gcPtr(new PointCommand(coord1.getMidpoint(coord2)));
}


