#include <iostream>
#include "src/utils.hpp"

int main(int argc, char**  args){
    if (argc != 3){
        std::cerr << "Incorrect number of args! Should be main.c inFilename outFilename" << std::endl;
        return 1;
    }
    mainFunction(args[1], args[2]);
    return 0;
}