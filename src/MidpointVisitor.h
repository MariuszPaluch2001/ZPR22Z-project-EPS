//
// Created by kacper on 28.11.2022.
//

#ifndef ZPR_MIDPOINTVISITOR_H
#define ZPR_MIDPOINTVISITOR_H
#include "Visitor.h"
class MidpointLeftLineVisitor : public LeftLineVisitor {
private:
    gcPtr gc_;
public:
    MidpointLeftLineVisitor(const LeftOrientedLineCommand & ll) : LeftLineVisitor(ll), gc_(nullptr) {}
    virtual void visit( const LeftOrientedLineCommand & ll );
    virtual void visit( const RightOrientedLineCommand & rl );
    virtual void visit( const PointCommand & p );
    gcPtr getValue() const { return gc_; }
};

class MidpointRightLineVisitor : public RightLineVisitor {
private:
    gcPtr gc_;
public:
    MidpointRightLineVisitor(const RightOrientedLineCommand & rl) : RightLineVisitor(rl), gc_(nullptr) {}
    virtual void visit( const LeftOrientedLineCommand & ll );
    virtual void visit( const RightOrientedLineCommand & rl );
    virtual void visit( const PointCommand & p );
    gcPtr getValue() const { return gc_; }
};

class MidpointPointVisitor : public PointVisitor {
private:
    gcPtr gc_;
public:
    MidpointPointVisitor(const PointCommand & p) : PointVisitor(p), gc_(nullptr) {}
    virtual void visit( const LeftOrientedLineCommand & ll );
    virtual void visit( const RightOrientedLineCommand & rl );
    virtual void visit( const PointCommand & p );
    gcPtr getValue() const { return gc_; }
};



#endif //ZPR_MIDPOINTVISITOR_H
