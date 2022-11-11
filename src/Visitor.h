//
// Created by kacper on 05.11.2022.
//

#ifndef ZPR_VISITOR_H
#define ZPR_VISITOR_H
#include "GraphicCommands.h"

template <typename T /* return value of visitor */> class Visitor {
public:
    virtual ~Visitor() = default;
    virtual T visit( const LeftOrientedLineCommand & ll ) const = 0;
    virtual T visit( const RightOrientedLineCommand & rl ) const = 0;
    virtual T visit( const PointCommand & p ) const = 0;
};

template <typename T> class LeftLineVisitor : public Visitor<T> {
protected:
    const LeftOrientedLineCommand & ll_;
public:
    LeftLineVisitor(const LeftOrientedLineCommand & ll ) : ll_( ll ) {}
    virtual T visit( const LeftOrientedLineCommand & ll ) const;
    virtual T visit( const RightOrientedLineCommand & rl ) const;
    virtual T visit( const PointCommand & p ) const;
};

template <typename T> class RightLineVisitor : public Visitor<T> {
protected:
    const RightOrientedLineCommand & rl_;
public:
    RightLineVisitor(const RightOrientedLineCommand & rl ) : rl_( rl ) {}
    virtual T visit( const LeftOrientedLineCommand & ll ) const;
    virtual T visit( const RightOrientedLineCommand & rl ) const;
    virtual T visit( const PointCommand & p ) const ;
};

template <typename T> class PointVisitor : public Visitor<T>  {
protected:
    const PointCommand & p_;
public:
    PointVisitor(const PointCommand & p ) : p_( p ) {}
    virtual T visit( const LeftOrientedLineCommand & ll ) const ;
    virtual T visit( const RightOrientedLineCommand & rl ) const;
    virtual T visit( const PointCommand & p ) const;
};

//if we ever need to have few Visitors returning eg. double, we will use inheritance (DifferenceVisitor inheriting from
// Visitor<double>
using gcPtr =  std::unique_ptr<GraphicCommand>;
using MidpointVisitor = Visitor<gcPtr>;
using LeftLineMidpointVisitor = LeftLineVisitor<gcPtr>;
using RightLineMidpointVisitor = RightLineVisitor<gcPtr>;
using PointMidpointVisitor = PointVisitor<gcPtr>;

using DifferenceVisitor = Visitor<double>;
using LeftLineDifferenceVisitor = LeftLineVisitor<double>;
using RightLineDifferenceVisitor = RightLineVisitor<double>;
using PointDifferenceVisitor = PointVisitor<double>;
#endif //ZPR_VISITOR_H
