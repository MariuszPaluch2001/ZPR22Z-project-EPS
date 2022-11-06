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
    std::vector<std::string> headerLines;
    std::fstream fileHandle_;
    unsigned maxPortionSize_;
    Resolution resolution_;
    Resolution readResolution();
    void readHeader();
public:
    PictureEPS(const std::string& epsFileName, unsigned maxPortionSize) : maxPortionSize_(maxPortionSize)
    {
        fileHandle_.open(epsFileName, std::ios::in);
        try
        {
            if (!fileHandle_)
                throw std::ios::failure( "Error opening file!" );
        }
        catch( const std::exception& e ) {
            std::cerr << e.what() << '\n';
        }
        readHeader();
        resolution_ = readResolution();

    }
    ~PictureEPS() { fileHandle_.close(); }
    std::vector<std::string> getHeaderLines() { return  headerLines; }


};


#endif //ZPR_PICTUREEPS_H
