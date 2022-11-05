//
// Created by mariusz on 05.11.22.
//

#include "PictureEPS.h"
#include <algorithm>
#include <iostream>
#include <sstream>

void PictureEPS::readHeader() {
    std::string line;
    while (std::getline(fileHandle_, line)){
        if (line.rfind("%%", 0) == 0 || line.rfind("%!", 0) == 0){
            headerLines.push_back(line);
        }
        else{
            break;
        }
    }
}

Resolution PictureEPS::readResolution(){
    int xRes = 0;
    int yRes = 0;
    for (std::string line : headerLines){
        if (line.rfind("%%BoundingBox", 0) == 0){
            std::stringstream s(line);
            std::string tag, zero1, zero2, x, y;
            s >> tag >> zero1 >> zero2 >> x >> y;
            xRes = std::stoi(x);
            yRes = std::stoi(y);
        }
    }
    return Resolution(xRes,yRes);
}