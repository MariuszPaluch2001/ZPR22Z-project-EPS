//
// Created by mariusz on 08.11.22.
//
/*
    File EPSFileTools.h contains class definitions representing the File Header,
    and classes representing input and output files. They are used to read text
   from input, pass data to algorithm and send data to output file.
*/
#ifndef ZPR_EPSFILETOOLS_H
#define ZPR_EPSFILETOOLS_H
#include <fstream>
#include <memory>
#include <variant>

#include "Algorithm.hpp"
#include "EPSCommandRepresentation.h"
#include "GraphicCommands.h"
#include "Scalar2DRepresentation.h"

using RelativeCommandVar= std::variant<LeftOrientedLineCommand, RightOrientedLineCommand>;
using AbsoluteCommandVar = std::variant<PointCommand, MoveCommand>;

/*
 * using VariantCommand = std::variant<NonProcessableCommand, RelativeCommandVar, AbsoluteCommandVar>
 */
using VariantCommand =
    std::variant<NonProcessableCommand, RelativeCommandVar, PointCommand>;

class Header {
  Resolution resolution_;
  std::string header_;
  static Resolution findResolution(const std::string &header);
  std::string setResolutionInHeader();
public:
  explicit Header(const std::string &header) : resolution_(findResolution(header)), header_(header) {}
  void setResolution(const Resolution &resolution);
  std::string getHeaderString() const { return header_; }
  Resolution getResolution() const { return resolution_; }
};

/*
    This class represent input file. As arguments in constructor class require
    reference to input stream. Before reading commands, class's object should
   read header by call method 'getHeader', otherwise method getCommand throw
   runtime exception. Class don't close the input stream.
*/
class EPSInFileStream {
  std::istream &file_;
  bool was_header_read = false;

  std::string readHeader();
  static CoordinateValue readPoint(const std::string &commandLine);
  static std::string stripCommandSignature(const std::string &commandLine);
  static VariantCommand
  makeVariantCommand(const std::string &command_line,
                     const std::string &command_signature);
  std::string getCommandLine();
public:
  explicit EPSInFileStream(std::istream &f) : file_(f) {}
  EPSInFileStream(const EPSInFileStream &) = delete;
  EPSInFileStream &operator=(const EPSInFileStream &) = delete;
  Header getHeader();
  VariantCommand getCommand();
  bool isFinished() const { return file_.peek() == EOF; }
  bool isNextRelative();
  bool isNextAbsolute();
  bool isNextUnprocessable();
};

/*
    This class represent output file. As arguments in constructor class require
    reference to output stream. Before writing commands, class's object should
   write header by call method 'putHeader', otherwise method putCommand throw
   runtime exception. Class don't close the output stream.
*/
class EPSOutFileStream {
  std::ostream &file_;
  bool was_header_write = false;

public:
  explicit EPSOutFileStream(std::ostream &f) : file_(f) {}
  EPSOutFileStream(const EPSOutFileStream &) = delete;
  EPSOutFileStream &operator=(const EPSOutFileStream &) = delete;
  void putHeader(Header &header);
  void putCommand(Command &c);
};

#endif // ZPR_EPSFILETOOLS_H
