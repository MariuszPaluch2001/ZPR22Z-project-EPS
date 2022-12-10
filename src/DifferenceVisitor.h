//
// Created by kacper on 28.11.2022.
//

#ifndef ZPR_DIFFERENCEVISITOR_H
#define ZPR_DIFFERENCEVISITOR_H
#include "Visitor.h"
//@todo maybe dual base virtual inherition?
extern const double MAX_DIFFERENCE;
class DifferenceLeftLineVisitor : public LeftLineVisitor {
private:
  double value_;

public:
  DifferenceLeftLineVisitor(const LeftOrientedLineCommand &ll)
      : LeftLineVisitor(ll), value_(0) {}
  virtual void visit(const LeftOrientedLineCommand &ll);
  virtual void visit(const RightOrientedLineCommand &rl);
  virtual void visit(const PointCommand &p);
  double getValue() const { return value_; }
};

class DifferenceRightLineVisitor : public RightLineVisitor {
private:
  double value_;

public:
  DifferenceRightLineVisitor(const RightOrientedLineCommand &rl)
      : RightLineVisitor(rl), value_(0) {}
  virtual void visit(const LeftOrientedLineCommand &ll);
  virtual void visit(const RightOrientedLineCommand &rl);
  virtual void visit(const PointCommand &p);
  double getValue() const { return value_; }
};

class DifferencePointVisitor : public PointVisitor {
private:
  double value_;

public:
  DifferencePointVisitor(const PointCommand &p) : PointVisitor(p), value_(0) {}
  virtual void visit(const LeftOrientedLineCommand &ll);
  virtual void visit(const RightOrientedLineCommand &rl);
  virtual void visit(const PointCommand &p);
  double getValue() const { return value_; }
};

#endif // ZPR_DIFFERENCEVISITOR_H
