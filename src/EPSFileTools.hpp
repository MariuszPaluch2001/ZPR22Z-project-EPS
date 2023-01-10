//
// Created by mariusz on 08.11.22.
//
//
//    File EPSFileTools.h contains class definitions representing the File
//    Header, and classes representing input and output files. They are used to
//    read text from input, pass data to algorithm and send data to output file.
//
#ifndef ZPR_EPSFILETOOLS_HPP
#define ZPR_EPSFILETOOLS_HPP
#include <fstream>
#include <memory>
#include <variant>

#include "Algorithm.hpp"
#include "EPSCommandRepresentation.h"
#include "GraphicCommands.h"
#include "Scalar2DRepresentation.h"

class Header {
  Resolution resolution_;
  std::string header_;
  static Resolution findResolution(const std::string &header);
  std::string setResolutionInHeader() const;

public:
  explicit Header(const std::string &header)
      : resolution_(findResolution(header)), header_(header) {}
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
class EPSInFile {
  std::istream &file_;
  bool was_header_read = false;

  std::string readHeader();
  static CoordinateValue readPoint(const std::string &commandLine);
  static std::string stripCommandSignature(const std::string &commandLine);
  std::string getCommandLine();

public:
  explicit EPSInFile(std::istream &f) : file_(f) {}
  EPSInFile(const EPSInFile &) = delete;
  EPSInFile &operator=(const EPSInFile &) = delete;
  Header getHeader();
  bool isFinished() { return file_.peek() == EOF; }
  bool isNextRelative();
  bool isNextAbsolute();
  bool isNextUnprocessable();
  RelativeCommandVar getRelativeCommandVar();
  AbsoluteCommandVar getAbsoluteCommandVar();
  NonProcessableCommand getNonProcessableCommand();
};

/*
    This class represent output file. As arguments in constructor class require
    reference to output stream. Before writing commands, class's object should
    write header by call method 'putHeader', otherwise method putCommand throw
    runtime exception. Class don't close the output stream.
*/
class EPSOutFile {
  std::ostream &file_;
  bool was_header_write = false;

public:
  explicit EPSOutFile(std::ostream &f) : file_(f) {}
  EPSOutFile(const EPSOutFile &) = delete;
  EPSOutFile &operator=(const EPSOutFile &) = delete;
  void putHeader(Header &header);
  void putCommand(const Command &c);
  void putCommand(const std::string &c);
  template <typename BATCH_TYPE> void putBatch(const BATCH_TYPE &batch);
};

static auto stringVisit = [](const auto &command) {
  return command.toString();
};

template <typename BATCH_TYPE>
void EPSOutFile::putBatch(const BATCH_TYPE &batch) {
  for (auto command : batch)
    putCommand(std::visit(stringVisit, command));
}
#endif // ZPR_EPSFILETOOLS_HPP
