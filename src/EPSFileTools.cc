//
// Created by mariusz on 08.11.22.
//
#include "EPSFileTools.h"
#include <sstream>

Resolution Header::findResolution(){
    int xRes = 0;
    int yRes = 0;
    std::string line;
    std::stringstream ss(header_);

    while(getline(ss, line, '\n')){
        if (line.rfind("%%BoundingBox", 0) == 0){
            std::stringstream s(line);
            std::string tag, zero1, zero2, x, y;
            s >> tag >> zero1 >> zero2 >> x >> y;
            xRes = std::stoi(x);
            yRes = std::stoi(y);
        }
    }
    return Resolution(xRes, yRes);
}

void Header::setResolution( const Resolution & resolution ){
    resolution_.setX(resolution.getX());
    resolution_.setY(resolution.getY());
}

std::string EPSInFileStream::readHeader() {
    char text[256];
    std::string textString;
    std::string headerBuffor;
    if (!wasHeaderRead){
        while (std::ifstream::getline(text, 256))
            {
                textString = std::string(text);
                if (textString == "%%EndComments")
                    break;
                headerBuffor += '\n' + textString;
            }
    }
    else
        throw  std::runtime_error("Header was read.");

    wasHeaderRead = true;

    return headerBuffor;
}

Header EPSInFileStream::getHeader() {
    std::string headerStr = readHeader();
    Header header(headerStr);
    return  header;
}

EPSInFileStream & EPSInFileStream::operator>>( cPtr & ptr ){
    if(!wasHeaderRead){
        ptr->toString();
    }
    return *this;
}