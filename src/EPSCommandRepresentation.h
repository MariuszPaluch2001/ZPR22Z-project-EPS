//
// Created by kacper on 04.11.2022.
//

#ifndef ZPR_EPSCOMMANDREPRESENTATION_H
#define ZPR_EPSCOMMANDREPRESENTATION_H
#include <iostream>
class Command {
public:
    virtual std::string toString() const = 0;
};

std::ostream & operator<<(std::ostream & os, const Command & com);

#endif //ZPR_EPSCOMMANDREPRESENTATION_H
