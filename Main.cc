#include <iostream>
#include <variant>

#include "src/EPSFileTools.hpp"
#include "src/EPSCommandRepresentation.h"
#include "src/GraphicCommands.h"
#include "src/Algorithm.hpp"

template <typename BATCH_TYPE>
void put_batch_with_processing(BATCH_TYPE&, EPSOutFile &, const Algorithm &);
void handle_relative_command(RelativeBatch &, AbsoluteBatch &, EPSInFile &, EPSOutFile &, const Algorithm &);
void handle_absolute_command(RelativeBatch &, AbsoluteBatch &, EPSInFile &, EPSOutFile &, const Algorithm &);
void handle_nonprocessable_command(RelativeBatch &, AbsoluteBatch &, EPSInFile &, EPSOutFile &, const Algorithm &);

int main(int argc, char**  args){
    if (argc != 3){
        std::cerr << "Incorrect number of args! Should be main.c inFilename outFilename" << std::endl;
        return 1;
    }

    const int MAX_NUMBER_COMMANDS = 10000;

    double scale = 0.5;
    std::ifstream file_in(args[1]);
    std::ofstream file_out(args[2]);
    EPSInFile eps_in_file(file_in);
    EPSOutFile eps_out_file(file_out);


    AbsoluteBatch abs_batch;
    RelativeBatch rel_batch;

    Header header = eps_in_file.getHeader();
    header.setResolution(header.getResolution() * scale);
    Algorithm algorithm(1, scale);
    eps_out_file.putHeader(header);

    while(!eps_in_file.isFinished()){
        if (abs_batch.size() == MAX_NUMBER_COMMANDS)
            put_batch_with_processing(abs_batch, eps_out_file, algorithm);
        if (rel_batch.size() == MAX_NUMBER_COMMANDS)
            put_batch_with_processing(rel_batch, eps_out_file, algorithm);
        if (eps_in_file.isNextAbsolute())
            handle_absolute_command(rel_batch, abs_batch, eps_in_file, eps_out_file, algorithm);
        else if (eps_in_file.isNextRelative())
            handle_relative_command(rel_batch, abs_batch, eps_in_file, eps_out_file, algorithm);
        else if (eps_in_file.isNextUnprocessable())
            handle_nonprocessable_command(rel_batch, abs_batch, eps_in_file, eps_out_file, algorithm);
    }
    if (!rel_batch.empty())
        put_batch_with_processing(rel_batch, eps_out_file, algorithm);
    if (!abs_batch.empty())
        put_batch_with_processing(abs_batch, eps_out_file, algorithm);
    return 0;
}


template <typename BATCH_TYPE>
void put_batch_with_processing(BATCH_TYPE& batch, EPSOutFile & file, const Algorithm & algo) {
    algo.template rescaleBatch(batch);
    algo.template sortBatch(batch);
    file.template putBatch(algo.template processBatch(batch));
    batch.clear();
}

void handle_relative_command(RelativeBatch & rel_batch, AbsoluteBatch & abs_batch, EPSInFile & in_file, EPSOutFile & out_file, const Algorithm & algo) {
    if (!abs_batch.empty())
        put_batch_with_processing(abs_batch, out_file, algo);
    rel_batch.push_back(in_file.getRelativeCommandVar());
}

void handle_absolute_command(RelativeBatch & rel_batch, AbsoluteBatch & abs_batch, EPSInFile & in_file, EPSOutFile & out_file, const Algorithm & algo) {

        if (!rel_batch.empty())
            put_batch_with_processing(rel_batch, out_file, algo);
        abs_batch.push_back(in_file.getAbsoluteCommandVar());

}
void handle_nonprocessable_command(RelativeBatch & rel_batch, AbsoluteBatch & abs_batch, EPSInFile & in_file, EPSOutFile & out_file, const Algorithm & algo)  {
    if (!rel_batch.empty())
        put_batch_with_processing(rel_batch, out_file, algo);
    if (!abs_batch.empty())
        put_batch_with_processing(abs_batch, out_file, algo);
    out_file.putCommand(in_file.getNonProcessableCommand());
}