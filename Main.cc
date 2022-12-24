#include <iostream>
#include <variant>

#include "src/EPSFileTools.h"
#include "src/EPSCommandRepresentation.h"
#include "src/GraphicCommands.h"
#include "src/Algorithm.h"

int main(int argc, char**  args){
    if (argc != 3){
        std::cerr << "Incorrect number of args! Should be main.c inFilename outFilename" << std::endl;
        return 1;
    }

    const int MAX_NUMBER_COMMANDS = 10000;
    RelativeCommand * command;
    RelativeBatch process_graphic_vec;

    double scale = 0.5;
    std::ifstream file_in(args[1]);
    std::ofstream file_out(args[2]);
    EPSInFileStream eps_in_file(file_in);
    EPSOutFileStream eps_out_file(file_out);
    Header header = eps_in_file.getHeader();
    header.setResolution(header.getResolution() * scale); // We don't change resolution ... so far.
    Algorithm algorithm(0.01);
    eps_out_file.putHeader(header);

    while(!eps_in_file.isFinished()){

        auto variant_command = eps_in_file.getCommand();
        auto not_process_command = std::get_if<NonProcessableCommand>(&variant_command);
        auto point_command = std::get_if<PointCommand>(&variant_command);

        if (not_process_command || point_command || process_graphic_vec.size() >= MAX_NUMBER_COMMANDS){
            algorithm.rescaleRelativeBatch(process_graphic_vec);
            process_graphic_vec = algorithm.processRelativeBatch(process_graphic_vec);

            for (auto var : process_graphic_vec){
                if ((command = std::get_if<LeftOrientedLineCommand>(&var)) ||
                        (command = std::get_if<RightOrientedLineCommand>(&var)))
                        eps_out_file.putCommand(*command);

            }

            if (not_process_command)
                eps_out_file.putCommand(*not_process_command);
            else if (point_command)
                eps_out_file.putCommand(*point_command);
            process_graphic_vec.clear();
        }
        else{
            process_graphic_vec.push_back(*std::get_if<RelativeCommandVar>(&variant_command));
        }
    }
    if (!process_graphic_vec.empty()){
        algorithm.rescaleRelativeBatch(process_graphic_vec);
        process_graphic_vec = algorithm.processRelativeBatch(process_graphic_vec);
        for (auto var : process_graphic_vec){

            if ((command = std::get_if<LeftOrientedLineCommand>(&var)) ||
                (command = std::get_if<RightOrientedLineCommand>(&var))){
                eps_out_file.putCommand(*command);
            }

        }
        process_graphic_vec.clear();
    }
    return 0;
}
