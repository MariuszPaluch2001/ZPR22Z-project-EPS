#include <iostream>
#include "src/EPSFileTools.h"
#include "src/EPSCommandRepresentation.h"
#include "src/GraphicCommands.h"
#include "src/Algorithm.h"
#include <variant>

int main(int argc, char**  args){
    if (argc != 3){
        std::cerr << "Incorrect number of args! Should be main.c inFilename outFilename" << std::endl;
        return 1;
    }
    std::ifstream fileIn(args[1]);
    std::ofstream fileOut(args[2]);
    GraphicCommand * command;
    EPSInFileStream epsInFile(fileIn);
    EPSOutFileStream epsOutFile(fileOut);
    Header h(epsInFile.getHeader());
    h.setResolution(h.getResolution()); // We don't change resolution ... so far.
    Algorithm algorithm(h.getResolution());
    ProcessableGraphicVector v;
    epsOutFile.putHeader(h);
    const int maxNumberCommands = 1000;
    while(!epsInFile.isFinished()){
        auto vc = epsInFile.getCommand();
        auto npc = std::get_if<NonProcessableCommand>(&vc);
        if (npc || v.size() >= maxNumberCommands){
            v = algorithm.processBatch(v);
            for (auto var : v){

                if ((command = std::get_if<LeftOrientedLineCommand>(&var)) ||
                        (command = std::get_if<RightOrientedLineCommand>(&var)) ||
                        (command = std::get_if<PointCommand>(&var))){
                        epsOutFile.putCommand(*command);
                }

            }
            if (npc)
                epsOutFile.putCommand(*npc);
            v.clear();
        }
        else{
            v.push_back(*std::get_if<ProcessableGraphicVar>(&vc));
        }
    }
    if (!v.empty()){
        v = algorithm.processBatch(v);
        for (auto var : v){

            if ((command = std::get_if<LeftOrientedLineCommand>(&var)) ||
                (command = std::get_if<RightOrientedLineCommand>(&var)) ||
                (command = std::get_if<PointCommand>(&var))){
                epsOutFile.putCommand(*command);
            }

        }
        v.clear();
    }
    return 0;
}
