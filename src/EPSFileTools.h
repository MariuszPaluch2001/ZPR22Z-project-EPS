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

#include "Algorithm.h"
#include "EPSCommandRepresentation.h"
#include "GraphicCommands.h"
#include "Scalar2DRepresentation.h"

using VariantCommand =
    std::variant<NonProcessableCommand, ProcessableGraphicVar>;

class Header {
  Resolution resolution_;
  std::string header_;
  Resolution findResolution();

public:
    ///używaj list inicjacyjnych konstruktora
    ///findResolution może przyjmować header jako argument - wtedy można wywalić default konstruktor z Resolution
  explicit Header(const std::string &header) {
    header_ = header;
    resolution_ = findResolution();
  };
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
  static Coordinates readPoint(const std::string &commandLine);
  static std::string stripCommandSignature(const std::string &commandLine);
  static VariantCommand
  makeVariantCommand(const std::string &command_line,
                     const std::string &command_signature);

public:
  explicit EPSInFileStream(std::istream &f) : file_(f) {}
  ///ma być const EPSInFIleStream! - i w kopii, i w przypisaniu
  EPSInFileStream(EPSInFileStream &) = delete;
  EPSInFileStream &operator=(EPSInFileStream &) = delete;
  Header getHeader();
  VariantCommand getCommand();
  ///isFinished może być  const
  bool isFinished() { return file_.peek() == EOF; }
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
  ///to samo co wyżej
  EPSOutFileStream(EPSOutFileStream &) = delete;
  EPSOutFileStream &operator=(EPSOutFileStream &) = delete;
  void putHeader(Header &header);
  void putCommand(Command &c);
};

#endif // ZPR_EPSFILETOOLS_H
