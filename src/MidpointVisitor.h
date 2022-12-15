//
// Created by kacper on 28.11.2022.
// File contains classes used to determine "middle point" between two graphic
// commands eg. two adjacent, colinear lines can be replaced by one
//

#ifndef ZPR_MIDPOINTVISITOR_H
#define ZPR_MIDPOINTVISITOR_H
#include "Visitor.h"
#include <optional>
#include <variant>

using VarGraphic = std::variant<LeftOrientedLineCommand,
                                RightOrientedLineCommand, PointCommand>;
using OptGraphic = std::optional<VarGraphic>;

using MidpointCarrier = ValueCarrier<OptGraphic>;

/*
 *  Class used to determine middle point between Left Line and other graphic
 * commands
 */
class MidpointLeftLineVisitor : public LeftLineVisitor, public MidpointCarrier {
private:
  OptGraphic gc_;

public:
  MidpointLeftLineVisitor(const LeftOrientedLineCommand &ll)
      : LeftLineVisitor(ll) {}
  virtual void visit(const LeftOrientedLineCommand &ll);
  virtual void visit(const RightOrientedLineCommand &rl);
  virtual void visit(const PointCommand &p);
  OptGraphic getValue() const { return gc_; }
};

/*
 *  Class used to determine middle point between Right Line and other graphic
 * commands
 */
class MidpointRightLineVisitor : public RightLineVisitor, MidpointCarrier {
private:
  OptGraphic gc_;

public:
  MidpointRightLineVisitor(const RightOrientedLineCommand &rl)
      : RightLineVisitor(rl) {}
  virtual void visit(const LeftOrientedLineCommand &ll);
  virtual void visit(const RightOrientedLineCommand &rl);
  virtual void visit(const PointCommand &p);
  OptGraphic getValue() const { return gc_; }
};

/*
 *  Class used to determine middle point between Point and other graphic
 * commands
 */
class MidpointPointVisitor : public PointVisitor, MidpointCarrier {
private:
  OptGraphic gc_;

public:
  MidpointPointVisitor(const PointCommand &p) : PointVisitor(p) {}
  virtual void visit(const LeftOrientedLineCommand &ll);
  virtual void visit(const RightOrientedLineCommand &rl);
  virtual void visit(const PointCommand &p);
  OptGraphic getValue() const { return gc_; }
};

#endif // ZPR_MIDPOINTVISITOR_H
