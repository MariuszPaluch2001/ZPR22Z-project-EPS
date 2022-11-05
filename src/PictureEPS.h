//
// Created by mariusz on 05.11.22.
//

#ifndef ZPR_PICTUREEPS_H
#define ZPR_PICTUREEPS_H
#include "Scalar2DRepresentation.h"
#include <fstream>
#include <iostream>
#include <vector>

class PictureEPS {
    std::fstream fileHandle_;
    unsigned maxPortionSize_;
    Resolution resolution_;
    std::vector<std::string> headerLines;
    void readHeader();
    Resolution readResolution();

public:
    PictureEPS(std::string epsFileName, unsigned maxPortionSize): maxPortionSize_(maxPortionSize)
    {
        fileHandle_.open(epsFileName, std::ios::in);
        if (!fileHandle_){
            std::cerr << "Temporary error" << std::endl;
        }
        readHeader();
        resolution_ = readResolution();

    }
    std::vector<std::string> getHeaderLines() {return  headerLines;};


};


#endif //ZPR_PICTUREEPS_H
