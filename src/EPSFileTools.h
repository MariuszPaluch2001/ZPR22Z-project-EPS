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
    std::string getHeaderString() { return header_; }
};

class EPSInFileStream : public std::ifstream {
    bool lastCommandProcessable = false;
    bool wasHeaderRead = false;
    std::string readHeader();
public:
    explicit EPSInFileStream( const std::string & fileName ) : std::ifstream( fileName ) { }
    Header getHeader();
    EPSInFileStream & operator>>( cPtr & ptr );
    bool wasLastCommandProcessable() const { return lastCommandProcessable; }
};

class EPSOutFileStream : public std::ofstream {
public:
    explicit EPSOutFileStream( const std::string & fileName ) : std::ofstream( fileName ) {}
    void writeHeader( const Header & h );
    EPSInFileStream & operator<<( const Header & h );

    EPSInFileStream & operator<<( const cPtr & ptr ); //użyj ptr->toString()
};

#endif //ZPR_EPSFILETOOLS_H
