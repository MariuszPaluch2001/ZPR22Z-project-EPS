//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_EPSCOMMANDREPRESENTATION_H
#define ZPR_EPSCOMMANDREPRESENTATION_H
#include <iostream>
class Command {
public:
    virtual std::string toString() const = 0;
    virtual ~Command() = default;
};

std::ostream & operator<<( std::ostream & os, const Command & com );

class UnspecifiedCommand : public Command {
    std::string textRepresentation_;
public:
    UnspecifiedCommand( const std::string & s) : textRepresentation_( s ) {}
    std::string toString() const { return textRepresentation_; }
};
#endif //ZPR_EPSCOMMANDREPRESENTATION_H
