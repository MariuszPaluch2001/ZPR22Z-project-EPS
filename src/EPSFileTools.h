//
// Created by mariusz on 08.11.22.
//

#ifndef ZPR_EPSFILETOOLS_H
#define ZPR_EPSFILETOOLS_H
#include <fstream>
#include <memory>
#include <variant>

#include "Scalar2DRepresentation.h"
#include "EPSCommandRepresentation.h"
#include "GraphicCommands.h"

// @TODO
// isFinished()
// testy

class Header {
    Resolution resolution_;
    std::string header_;
    Resolution findResolution();
public:
    explicit Header( const std::string & header ) {
        header_ = header;
        resolution_ = findResolution();
    };
    void setResolution( const Resolution & resolution );
    std::string getHeaderString() const { return header_; }
    Resolution getResolution() const { return resolution_; }
};
using variantCommand = std::variant<NonProcessableCommand, LeftOrientedLineCommand, RightOrientedLineCommand, PointCommand>;

class EPSInFileStream{
    std::istream& file;
    bool wasHeaderRead = false;
    std::string readHeader();
    static Point readPoint(const std::string& commandLine);
    static std::string stripCommandSignature(const std::string& commandLine);
    static variantCommand makeVariantCommand(const std::string & commandLine, const std::string & commandSignature);
public:
    explicit EPSInFileStream( std::istream& f ) : file(f) { }
    Header getHeader();
    variantCommand getCommand();
};

class EPSOutFileStream{
    std::ostream& file;
    bool wasHeaderWrite = false;
public:
    explicit EPSOutFileStream( std::ostream& f ) : file(f) { }
    void putHeader(Header& header);
    void putCommand(Command& c);
};

#endif //ZPR_EPSFILETOOLS_H
