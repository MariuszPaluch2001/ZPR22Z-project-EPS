//
// Created by kacper on 28.11.2022.
//

#ifndef ZPR_MIDPOINTVISITOR_H
#define ZPR_MIDPOINTVISITOR_H
#include "Visitor.h"
#include <variant>
#include <optional>
using varGraphic = std::variant<LeftOrientedLineCommand, RightOrientedLineCommand, PointCommand>;
using optGraphic = std::optional<varGraphic>;
class MidpointLeftLineVisitor : public LeftLineVisitor {
private:
    optGraphic gc_;
public:
    MidpointLeftLineVisitor(const LeftOrientedLineCommand & ll) : LeftLineVisitor(ll) {}
    virtual void visit( const LeftOrientedLineCommand & ll );
    virtual void visit( const RightOrientedLineCommand & rl );
    virtual void visit( const PointCommand & p );
    optGraphic getValue() const { return gc_; }
};

class MidpointRightLineVisitor : public RightLineVisitor {
private:
    optGraphic gc_;
public:
    MidpointRightLineVisitor(const RightOrientedLineCommand & rl) : RightLineVisitor(rl) {}
    virtual void visit( const LeftOrientedLineCommand & ll );
    virtual void visit( const RightOrientedLineCommand & rl );
    virtual void visit( const PointCommand & p );
    optGraphic getValue() const { return gc_; }
};

class MidpointPointVisitor : public PointVisitor {
private:
    optGraphic gc_;
public:
    MidpointPointVisitor(const PointCommand & p) : PointVisitor(p) {}
    virtual void visit( const LeftOrientedLineCommand & ll );
    virtual void visit( const RightOrientedLineCommand & rl );
    virtual void visit( const PointCommand & p );
    optGraphic getValue() const { return gc_; }
};



#endif //ZPR_MIDPOINTVISITOR_H
