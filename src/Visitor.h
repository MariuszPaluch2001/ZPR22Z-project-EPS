//
// Created by kacper on 05.11.2022.
//

#ifndef ZPR_VISITOR_H
#define ZPR_VISITOR_H
#include "GraphicCommands.h"

template <typename T /* return value of visitor */> class Visitor {
public:
    virtual ~Visitor() = default;
    virtual double visit( const LeftOrientedLineCommand & ll ) const = 0;
    virtual double visit( const RightOrientedLineCommand & rl ) const = 0;
    virtual double visit( const PointCommand & p ) const = 0;
};

template <typename T> class LeftLineVisitor : public Visitor<T> {
    const LeftOrientedLineCommand & ll_;
public:
    LeftLineVisitor(const LeftOrientedLineCommand & ll ) : ll_( ll ) {}
    virtual T visit( const LeftOrientedLineCommand & ll ) const { /* @todo implement*/ }
    virtual T visit( const RightOrientedLineCommand & rl ) const { /* @todo implement*/ }
    virtual T visit( const PointCommand & p ) const { /* @todo implement*/ }
};

template <typename T> class RightLineVisitor : public Visitor<T> {
    const RightOrientedLineCommand & rl_;
public:
    RightLineVisitor(const RightOrientedLineCommand & rl ) : rl_( rl ) {}
    virtual T visit( const LeftOrientedLineCommand & ll ) const { /* @todo implement*/ }
    virtual T visit( const RightOrientedLineCommand & rl ) const { /* @todo implement*/ }
    virtual T visit( const PointCommand & p ) const { /* @todo implement*/  }
};

template <typename T> class PointVisitor : public Visitor<T>  {
    const PointCommand & p_;
public:
    PointVisitor(const PointCommand & p ) : p_( p ) {}
    virtual T visit( const LeftOrientedLineCommand & ll ) const { /* @todo implement*/ }
    virtual T visit( const RightOrientedLineCommand & rl ) const { /* @todo implement*/  }
    virtual T visit( const PointCommand & p ) const { /* @todo implement*/  }
};

using MidpointVisitor = Visitor<std::unique_ptr<GraphicCommand>>;
using LeftLineMidpointVisitor = LeftLineVisitor<std::unique_ptr<GraphicCommand>>;
using RightLineMidpointVisitor = RightLineVisitor<std::unique_ptr<GraphicCommand>>;
using PointMidpointVisitor = PointVisitor<std::unique_ptr<GraphicCommand>>;

using DifferenceVisitor = Visitor<double>;
using LeftLineDifferenceVisitor = LeftLineVisitor<double>;
using RightLineDifferenceVisitor = RightLineVisitor<double>;
using PointDifferenceVisitor = PointVisitor<double>;
#endif //ZPR_VISITOR_H
