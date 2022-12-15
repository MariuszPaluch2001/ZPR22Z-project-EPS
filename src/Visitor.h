//
// Created by kacper on 05.11.2022.
// Files contains visitor classes, which will visit Graphical commands
//

#ifndef ZPR_VISITOR_H
#define ZPR_VISITOR_H
#include "GraphicCommands.h"

class Visitor {
public:
  virtual ~Visitor() = default;
  virtual void visit(const LeftOrientedLineCommand &ll) = 0;
  virtual void visit(const RightOrientedLineCommand &rl) = 0;
  virtual void visit(const PointCommand &p) = 0;
  Visitor() = default;
  Visitor(const Visitor &) = delete;
  Visitor &operator=(const Visitor &) = delete;
};

class LeftLineVisitor : public Visitor {
protected:
  const LeftOrientedLineCommand &ll_;

public:
  LeftLineVisitor(const LeftOrientedLineCommand &ll) : ll_(ll) {}
};

class RightLineVisitor : public Visitor {
protected:
  const RightOrientedLineCommand &rl_;

public:
  RightLineVisitor(const RightOrientedLineCommand &rl) : rl_(rl) {}
};

class PointVisitor : public Visitor {
protected:
  const PointCommand &p_;

public:
  PointVisitor(const PointCommand &p) : p_(p) {}
};

template <typename T> class ValueCarrier {
  T value_{};

protected:
  void setValue(const T &value) { value_ = value; }

public:
  T getValue() const { return value_; }
};
#endif // ZPR_VISITOR_H
