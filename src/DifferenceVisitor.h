//
// Created by kacper on 05.11.2022.
//

#ifndef ZPR_DIFFERENCEVISITOR_H
#define ZPR_DIFFERENCEVISITOR_H
#include "GraphicCommands.h"
class DifferenceVisitor {
public:
    virtual ~DifferenceVisitor() = default;
    virtual double visit( const LeftOrientedLineCommand & ll ) const = 0;
    virtual double visit( const RightOrientedLineCommand & rl ) const = 0;
    virtual double visit( const PointCommand & p ) const = 0;
};


class LeftLineDifferenceVisitor : public DifferenceVisitor {
    const LeftOrientedLineCommand & ll_;
public:
    LeftLineDifferenceVisitor(const LeftOrientedLineCommand & ll ) : ll_( ll ) {}
    virtual double visit( const LeftOrientedLineCommand & ll ) const { /* @todo implement*/ return 0; }
    virtual double visit( const RightOrientedLineCommand & rl ) const { /* @todo implement*/ return 0; }
    virtual double visit( const PointCommand & p ) const { /* @todo implement*/ return 0; }
};

class RightLineDifferenceVisitor : public DifferenceVisitor {
    const RightOrientedLineCommand & rl_;
public:
    RightLineDifferenceVisitor(const RightOrientedLineCommand & rl ) : rl_( rl ) {}
    virtual double visit( const LeftOrientedLineCommand & ll ) const { /* @todo implement*/ return 0; }
    virtual double visit( const RightOrientedLineCommand & rl ) const { /* @todo implement*/ return 0; }
    virtual double visit( const PointCommand & p ) const { /* @todo implement*/ return 0; }
};

class PointDifferenceVisitor : public DifferenceVisitor {
    const PointCommand & p_;
public:
    PointDifferenceVisitor(const PointCommand & p ) : p_( p ) {}
    virtual double visit( const LeftOrientedLineCommand & ll ) const { /* @todo implement*/ return 0; }
    virtual double visit( const RightOrientedLineCommand & rl ) const { /* @todo implement*/ return 0; }
    virtual double visit( const PointCommand & p ) const { /* @todo implement*/ return 0; }
};


#endif //ZPR_DIFFERENCEVISITOR_H
