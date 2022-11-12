//
// Created by mariusz on 08.11.22.
//

#ifndef ZPR_EPSFILETOOLS_H
#define ZPR_EPSFILETOOLS_H
#include <fstream>
#include "Scalar2DRepresentation.h"
#include "EPSCommandRepresentation.h"
#include <memory>
using cPtr = std::unique_ptr<Command>;

class Header {
    Resolution resolution_;
    std::string header_;
    Resolution findResolution();
public:
    explicit Header( const std::string & header ) {
        header_ = header;
        resolution_ = findResolution();
    };
    Resolution getResolution() const { return resolution_; }
    void setResolution( const Resolution & resolution );
    std::string getHeaderString() const { return header_; }
};

class EPSInFileStream : public std::ifstream {
    bool wasHeaderRead = false;
    std::string readHeader();
    cPtr readCommand();
    static Point readPoint(const std::string & commandLine);
    static std::string stripCommandSignature(const std::string & commandLine);
    cPtr makePointerOnCommand(const std::string & commandLine, const std::string & commandSignature);
public:
    explicit EPSInFileStream( const std::string & fileName ) : std::ifstream( fileName ) { }
    Header getHeader();
    EPSInFileStream & operator>>( cPtr & ptr );
    bool wasLastCommandProcessable() const { return lastCommandProcessable; }
};

class EPSOutFileStream : public std::ofstream {

public:
    explicit EPSOutFileStream( const std::string & fileName ) : std::ofstream( fileName ) {}
    EPSOutFileStream & operator<<( const Header & h );

    EPSOutFileStream & operator<<( const cPtr & ptr );
};

#endif //ZPR_EPSFILETOOLS_H
