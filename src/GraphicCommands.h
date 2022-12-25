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

class LeftOrientedLineCommand;
class RightOrientedLineCommand;
class PointCommand;
class MoveCommand;


class RelativeCommand : public ProcessableCommand {
public:
    RelativeCommand(const Direction &move) : ProcessableCommand(move) {}
    virtual std::string toString() const override = 0;
};

class AbsoluteCommand : public ProcessableCommand {
public:
    AbsoluteCommand(const Coordinates &move) : ProcessableCommand(move) {}
    virtual std::string toString() const override = 0;
};

class LeftOrientedLineCommand : public RelativeCommand {
public:
    LeftOrientedLineCommand(const Direction &move) : RelativeCommand(move) {}
    virtual std::string toString() const override;

};

class RightOrientedLineCommand : public RelativeCommand {
public:
    RightOrientedLineCommand(const Direction &move) : RelativeCommand(move) {}
    virtual std::string toString() const override;

};

class PointCommand : public AbsoluteCommand {
public:
    PointCommand(const Coordinates &coord) : AbsoluteCommand(coord) {}
    virtual std::string toString() const override;
};

class MoveCommand : public AbsoluteCommand {
public:
    MoveCommand(const Coordinates & coord) : AbsoluteCommand(coord) {}
    virtual std::string toString() const override;
};

using RelativeCommandVar = std::variant<LeftOrientedLineCommand, RightOrientedLineCommand>;
using AbsoluteCommandVar = std::variant<PointCommand, MoveCommand>;


/*
 * visitor functions
 */
extern const double MAX_DIFFERENCE;
double countDifference(const LeftOrientedLineCommand & ll1, const LeftOrientedLineCommand & ll2);
double countDifference(const LeftOrientedLineCommand & ll1, const RightOrientedLineCommand & rl2);
double countDifference(const RightOrientedLineCommand & rl1, const LeftOrientedLineCommand & ll2);
double countDifference(const RightOrientedLineCommand & rl1, const RightOrientedLineCommand & rl2);

double countDifference(const PointCommand & p1, const PointCommand & p2);
double countDifference(const PointCommand & p1, const MoveCommand & m2);
double countDifference(const MoveCommand & m1, const PointCommand & p2);
double countDifference(const MoveCommand & m1, const MoveCommand & m2);

RelativeCommandVar createMidpoint(const LeftOrientedLineCommand & ll1, const LeftOrientedLineCommand & ll2);
RelativeCommandVar createMidpoint(const LeftOrientedLineCommand & ll1, const RightOrientedLineCommand & rl2);
RelativeCommandVar createMidpoint(const RightOrientedLineCommand & rl1, const LeftOrientedLineCommand & ll2);
RelativeCommandVar createMidpoint(const RightOrientedLineCommand & rl1, const RightOrientedLineCommand & rl2);

AbsoluteCommandVar createMidpoint(const PointCommand & p1, const PointCommand & p2);
AbsoluteCommandVar createMidpoint(const PointCommand & p1, const MoveCommand & m2);
AbsoluteCommandVar createMidpoint(const MoveCommand & m1, const PointCommand & p2);
AbsoluteCommandVar createMidpoint(const MoveCommand & m1, const MoveCommand & m2);



#endif // ZPR_GRAPHICCOMMANDS_H
