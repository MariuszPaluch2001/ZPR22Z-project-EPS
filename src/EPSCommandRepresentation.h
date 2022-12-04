//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_EPSCOMMANDREPRESENTATION_H
#define ZPR_EPSCOMMANDREPRESENTATION_H
#include <iostream>
#include "Scalar2DRepresentation.h"
class Command {
public:
    virtual std::string toString() const = 0;
    virtual ~Command() = default;
};

std::ostream & operator<<( std::ostream & os, const Command & com );

class NonProcessableCommand : public Command {
    std::string textRepresentation_;
public:
    NonProcessableCommand( const std::string & s) : textRepresentation_( s ) {}
    std::string toString() const { return textRepresentation_; }
};



#endif //ZPR_EPSCOMMANDREPRESENTATION_H