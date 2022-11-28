//
// Created by kacper on 05.11.2022.
//

#ifndef ZPR_VISITOR_H
#define ZPR_VISITOR_H
#include "GraphicCommands.h"

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit( const LeftOrientedLineCommand & ll ) const = 0;
    virtual void visit( const RightOrientedLineCommand & rl ) const = 0;
    virtual void visit( const PointCommand & p ) const = 0;
};



class LeftLineVisitor : public Visitor {
protected:
    const LeftOrientedLineCommand & ll_;
public:
    LeftLineVisitor(const LeftOrientedLineCommand & ll ) : ll_( ll ) {}
    virtual void visit( const LeftOrientedLineCommand & ll ) const = 0;
    virtual void visit( const RightOrientedLineCommand & rl ) const = 0;
    virtual void visit( const PointCommand & p ) const = 0;
};

class RightLineVisitor : public Visitor {
protected:
    const RightOrientedLineCommand & rl_;
public:
    RightLineVisitor(const RightOrientedLineCommand & rl ) : rl_( rl ) {}
    virtual void visit( const LeftOrientedLineCommand & ll ) const = 0;
    virtual void visit( const RightOrientedLineCommand & rl ) const = 0;
    virtual void visit( const PointCommand & p ) const = 0;
};

class PointVisitor : public Visitor  {
protected:
    const PointCommand & p_;
public:
    PointVisitor(const PointCommand & p ) : p_( p ) {}
    virtual void visit( const LeftOrientedLineCommand & ll ) const = 0;
    virtual void visit( const RightOrientedLineCommand & rl ) const = 0;
    virtual void visit( const PointCommand & p ) const = 0;
};

using gcPtr =  std::unique_ptr<GraphicCommand>;

#endif //ZPR_VISITOR_H
