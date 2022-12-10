//
// Created by kacper on 06.11.2022.
//
#include "MidpointVisitor.h"
//@todo change dummy implementations
void MidpointLeftLineVisitor::visit(const LeftOrientedLineCommand& ll) {
    gc_ = ll_;
}

void MidpointLeftLineVisitor::visit(const RightOrientedLineCommand& rl) {
    gc_ = ll_;
}

void MidpointLeftLineVisitor::visit(const PointCommand& p) {
    gc_ = ll_;
}

void MidpointRightLineVisitor::visit(const LeftOrientedLineCommand& rl) {
    gc_ = rl_;
}

void MidpointRightLineVisitor::visit(const RightOrientedLineCommand& ll) {
    gc_ = rl_;
}

void MidpointRightLineVisitor::visit(const PointCommand& p) {
    gc_ = rl_;
}

void MidpointPointVisitor::visit(const LeftOrientedLineCommand& ll) {
    gc_ = p_;
}

void MidpointPointVisitor::visit(const RightOrientedLineCommand& ll) {
    gc_ = p_;
}

void MidpointPointVisitor::visit(const PointCommand& p) {
    gc_ = p_;
}

/*
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


*/