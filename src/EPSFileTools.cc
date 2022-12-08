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
    bool isResFound = false;
    while(std::getline(ss, line)){
        if (line.rfind("%%BoundingBox", 0) == 0){
            std::stringstream s(line);
            std::string tag, zero1, zero2, x, y;
            s >> tag >> zero1 >> zero2 >> x >> y;
            xRes = std::stoi(x);
            yRes = std::stoi(y);
            isResFound = true;
        }
    }
    if (!isResFound)
        throw  std::runtime_error("Resolution not founded.");
    return Resolution(xRes, yRes);
}

void Header::setResolution( const Resolution & resolution ){
    resolution_.setX(resolution.getX());
    resolution_.setY(resolution.getY());
}

std::string EPSInFileStream::readHeader() {
    std::string text;
    std::string headerBuffer;
    bool isFinishedFlag;
    if (!wasHeaderRead){
        isFinishedFlag = isFinished();
        while (!isFinishedFlag)
            {
                std::getline(file, text);
                if (text == "%%EndComments"){
                    headerBuffer += "%%EndComments\n";
                    break;
                }
                headerBuffer += text + '\n';
                isFinishedFlag = isFinished();
            }
        if (isFinishedFlag)
            throw  std::runtime_error("File is finished.");
    }
    else
        throw  std::runtime_error("Header has been read.");

    wasHeaderRead = true;
    return headerBuffer;
}

Header EPSInFileStream::getHeader() {
    std::string headerStr = readHeader();
    Header header(headerStr);
    return  header;
}

Point EPSInFileStream::readPoint(const std::string & commandLine){
    std::stringstream s(commandLine);
    std::string x, y;
    s >> x >> y ;
    return { std::stod(x), std::stod(y)};
}
std::string EPSInFileStream::stripCommandSignature(const std::string & commandLine){
    std::string commandSignature;
    std::size_t found;
    found = commandLine.find_last_of( ' ' );
    if (found != std::string::npos)
        commandSignature = commandLine.substr(found+1);
    else
        commandSignature = commandLine;

    return commandSignature;
}

variantCommand EPSInFileStream::makeVariantCommand(const std::string & commandLine, const std::string & commandSignature){
    if (commandSignature == "l") {
        return variantCommand(std::in_place_index<2>,
                RightOrientedLineCommand(Point(0.0,0.0),
                                         readPoint(commandLine)));
    }
    else if (commandSignature == "lineto"){
        return variantCommand(std::in_place_index<1>,
                LeftOrientedLineCommand(Point(0,0),
                                        readPoint(commandLine)));
    }
    else if (commandSignature == "p2"){
        return variantCommand(std::in_place_index<3>,
                PointCommand(readPoint(commandLine)));
    }
    else{
        return variantCommand(std::in_place_index<0>,
                NonProcessableCommand(commandLine));
    }
}

variantCommand EPSInFileStream::getCommand(){
        std::string text;
        std::string commandSignature;
        if(wasHeaderRead){
            if (!isFinished()){
                std::getline(file, text);
                commandSignature = stripCommandSignature(text);
                return makeVariantCommand(text, commandSignature);
            }
            else {
                throw std::runtime_error("File is finished.");
            }
        }
        else
            throw std::runtime_error("Header hasn't read yet.");

}

void EPSOutFileStream::putHeader(Header& header) {
    if (wasHeaderWrite)
        throw std::runtime_error("Header has already written.");
    std::string headerString = header.getHeaderString();
    file << headerString;
    wasHeaderWrite = true;
}

void EPSOutFileStream::putCommand(Command& c){
    if (!wasHeaderWrite)
        throw std::runtime_error("Header hasn't written.");
    file << c.toString();
}