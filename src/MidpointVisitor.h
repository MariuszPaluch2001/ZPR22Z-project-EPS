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
public:
  MidpointLeftLineVisitor(const LeftOrientedLineCommand &ll)
      : LeftLineVisitor(ll) {}
  virtual void visit(const LeftOrientedLineCommand &ll) override;
  virtual void visit(const RightOrientedLineCommand &rl) override;
  virtual void visit(const PointCommand &p) override;
};

/*
 *  Class used to determine middle point between Right Line and other graphic
 * commands
 */
class MidpointRightLineVisitor : public RightLineVisitor, public MidpointCarrier {
public:
  MidpointRightLineVisitor(const RightOrientedLineCommand &rl)
      : RightLineVisitor(rl) {}
  virtual void visit(const LeftOrientedLineCommand &ll) override;
  virtual void visit(const RightOrientedLineCommand &rl) override;
  virtual void visit(const PointCommand &p) override;
};

/*
 *  Class used to determine middle point between Point and other graphic
 * commands
 */
class MidpointPointVisitor : public PointVisitor, public MidpointCarrier {
public:
  MidpointPointVisitor(const PointCommand &p) : PointVisitor(p) {}
  virtual void visit(const LeftOrientedLineCommand &ll) override;
  virtual void visit(const RightOrientedLineCommand &rl) override;
  virtual void visit(const PointCommand &p) override;
};

#endif // ZPR_MIDPOINTVISITOR_H
