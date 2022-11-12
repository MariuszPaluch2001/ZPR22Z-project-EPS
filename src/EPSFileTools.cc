//
// Created by mariusz on 08.11.22.
//
#include "EPSFileTools.h"
#include "GraphicCommands.h"
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
    headerBuffor += '\n';
    return headerBuffor;
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
    return {std::stod(x),std::stod(y)};
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

cPtr EPSInFileStream::makePointerOnCommand(const std::string & commandLine, const std::string & commandSignature){
    if (commandSignature == "l") {
        return std::make_unique<RightOrientedLineCommand>(
                Point(0.0,0.0),
                readPoint(commandLine));
    }
    else if (commandSignature == "lineto"){
        return std::make_unique<LeftOrientedLineCommand>(
                Point(0,0),
                readPoint(commandLine));
    }
    else if (commandSignature == "p2"){
        return std::make_unique<PointCommand>(
                readPoint(commandLine));
    }
    else{
        return std::make_unique<NonProcessableCommand>(commandLine);
    }
}
cPtr EPSInFileStream::readCommand(){
        char text[256];
        std::string commandLine, commandSignature;
        if(wasHeaderRead){
            std::ifstream::getline(text, 256);
            commandLine = std::string(text);
            commandSignature = stripCommandSignature(commandLine);
            return makePointerOnCommand(commandLine, commandSignature);
        }
        else
            throw std::runtime_error("Header hasn't read yet.");

}
EPSInFileStream & EPSInFileStream::operator>>( cPtr & ptr ){
    ptr  = readCommand();
    return *this;
}

EPSOutFileStream & EPSOutFileStream::operator<<( const Header & h ){
    std::string headerString = h.getHeaderString();
    write(headerString.data(), headerString.size());
    write("%%EndComments\n", 14);
    return *this;
}

EPSOutFileStream & EPSOutFileStream::operator<<( const cPtr & ptr ){
    std::string commandString = ptr->toString();
    write(commandString.data(), commandString.size());
    return *this;
}