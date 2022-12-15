//
// Created by kacper on 28.11.2022.
// This file contains Visitor classes used for counting scaled difference
// between two adjacent commands. This difference will be used to determine
// whether we can substitute two commands by just one (and so on)
//

#ifndef ZPR_DIFFERENCEVISITOR_H
#define ZPR_DIFFERENCEVISITOR_H
#include "Visitor.h"
//@todo maybe dual base virtual inherition?
extern const double MAX_DIFFERENCE;
/*
 * class counts difference between Left Line and other graphic commannds
 */
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

/*
 * class counts difference between Right Line and other graphic commannds
 */
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

/*
 * class counts difference between Point and other graphic commannds
 */

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
