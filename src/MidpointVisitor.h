//
// Created by kacper on 28.11.2022.
//

#ifndef ZPR_MIDPOINTVISITOR_H
#define ZPR_MIDPOINTVISITOR_H
#include "Visitor.h"
#include <optional>
#include <variant>
using VarGraphic = std::variant<LeftOrientedLineCommand,
                                RightOrientedLineCommand, PointCommand>;
using OptGraphic = std::optional<VarGraphic>;
class MidpointLeftLineVisitor : public LeftLineVisitor {
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

class MidpointRightLineVisitor : public RightLineVisitor {
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

class MidpointPointVisitor : public PointVisitor {
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
