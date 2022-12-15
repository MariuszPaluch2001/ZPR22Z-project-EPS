//
// Created by kacper on 28.11.2022.
// This file contains Visitor classes used for counting scaled difference
// between two adjacent commands. This difference will be used to determine
// whether we can substitute two commands by just one (and so on)
//

#ifndef ZPR_DIFFERENCEVISITOR_H
#define ZPR_DIFFERENCEVISITOR_H
#include "Visitor.h"

using DifferenceCarrier = ValueCarrier<double>;
extern const double MAX_DIFFERENCE;

/*
 * class counts difference between Left Line and other graphic commannds
 */
class DifferenceLeftLineVisitor : public LeftLineVisitor,
                                  public DifferenceCarrier {

public:
  DifferenceLeftLineVisitor(const LeftOrientedLineCommand &ll)
      : LeftLineVisitor(ll) {}
  virtual void visit(const LeftOrientedLineCommand &ll) override;
  virtual void visit(const RightOrientedLineCommand &rl) override;
  virtual void visit(const PointCommand &p) override;
};

/*
 * class counts difference between Right Line and other graphic commannds
 */
class DifferenceRightLineVisitor : public RightLineVisitor,
                                   public DifferenceCarrier {
public:
  DifferenceRightLineVisitor(const RightOrientedLineCommand &rl)
      : RightLineVisitor(rl) {}
  virtual void visit(const LeftOrientedLineCommand &ll) override;
  virtual void visit(const RightOrientedLineCommand &rl) override;
  virtual void visit(const PointCommand &p) override;
};

/*
 * class counts difference between Point and other graphic commannds
 */

class DifferencePointVisitor : public PointVisitor, public DifferenceCarrier {
public:
  DifferencePointVisitor(const PointCommand &p) : PointVisitor(p) {}
  virtual void visit(const LeftOrientedLineCommand &ll) override;
  virtual void visit(const RightOrientedLineCommand &rl) override;
  virtual void visit(const PointCommand &p) override;
};

#endif // ZPR_DIFFERENCEVISITOR_H
