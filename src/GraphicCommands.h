//
// Created by kacper on 04.11.2022.
// File contains classes representing Processable Graphic Commands - the ones
// which we will try to compress
//

#ifndef ZPR_GRAPHICCOMMANDS_H
#define ZPR_GRAPHICCOMMANDS_H
#include "EPSCommandRepresentation.h"
#include <optional>
#include <variant>

/**
 * Klasa reprezentuje komendę względną - taką, której działanie zależy od
 * umiejscowienia kursora
 */
class RelativeCommand : public ProcessableCommand {
public:
  RelativeCommand(const Direction &move) : ProcessableCommand(move) {}
  virtual std::string toString() const override = 0;
};
/**
 * Klasa reprezentuje komendę bezwzględną - taką, której działanie nie zależy od
 * umiejscowienia kursora
 */
class AbsoluteCommand : public ProcessableCommand {
public:
  AbsoluteCommand(const Coordinates &move) : ProcessableCommand(move) {}
  virtual std::string toString() const override = 0;
};

class LeftLineCommand : public RelativeCommand {
public:
  LeftLineCommand(const Direction &move) : RelativeCommand(move) {}
  virtual std::string toString() const override;
};

class RightLineCommand : public RelativeCommand {
public:
  RightLineCommand(const Direction &move) : RelativeCommand(move) {}
  virtual std::string toString() const override;
};

class PointCommand : public AbsoluteCommand {
public:
  PointCommand(const Coordinates &coord) : AbsoluteCommand(coord) {}
  virtual std::string toString() const override;
};

class MoveCommand : public AbsoluteCommand {
public:
  MoveCommand(const Coordinates &coord) : AbsoluteCommand(coord) {}
  virtual std::string toString() const override;
};

using RelativeCommandVar = std::variant<LeftLineCommand, RightLineCommand>;
using AbsoluteCommandVar = std::variant<PointCommand, MoveCommand>;

/**
 * Maksymalna różnica między punktami
 */
extern const double MAX_DIFFERENCE;
/**
 * Funkcje wizytujące
 */
double countDifference(const LeftLineCommand &ll1, const LeftLineCommand &ll2);
double countDifference(const LeftLineCommand &ll1, const RightLineCommand &rl2);
double countDifference(const RightLineCommand &rl1, const LeftLineCommand &ll2);
double countDifference(const RightLineCommand &rl1,
                       const RightLineCommand &rl2);

double countDifference(const PointCommand &p1, const PointCommand &p2);
double countDifference(const PointCommand &p1, const MoveCommand &m2);
double countDifference(const MoveCommand &m1, const PointCommand &p2);
double countDifference(const MoveCommand &m1, const MoveCommand &m2);

RelativeCommandVar createMidpoint(const LeftLineCommand &ll1,
                                  const LeftLineCommand &ll2);
RelativeCommandVar createMidpoint(const LeftLineCommand &ll1,
                                  const RightLineCommand &rl2);
RelativeCommandVar createMidpoint(const RightLineCommand &rl1,
                                  const LeftLineCommand &ll2);
RelativeCommandVar createMidpoint(const RightLineCommand &rl1,
                                  const RightLineCommand &rl2);

AbsoluteCommandVar createMidpoint(const PointCommand &p1,
                                  const PointCommand &p2);
AbsoluteCommandVar createMidpoint(const PointCommand &p1,
                                  const MoveCommand &m2);
AbsoluteCommandVar createMidpoint(const MoveCommand &m1,
                                  const PointCommand &p2);
AbsoluteCommandVar createMidpoint(const MoveCommand &m1, const MoveCommand &m2);

#endif // ZPR_GRAPHICCOMMANDS_H
