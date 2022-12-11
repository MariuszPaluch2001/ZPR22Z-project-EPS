//
// Created by mariusz on 08.11.22.
//

#ifndef ZPR_EPSFILETOOLS_H
#define ZPR_EPSFILETOOLS_H
#include <fstream>
#include <memory>
#include <variant>

#include "EPSCommandRepresentation.h"
#include "GraphicCommands.h"
#include "Scalar2DRepresentation.h"
#include "Algorithm.h"

using VariantCommand =
        std::variant<NonProcessableCommand, ProcessableGraphicVar>;

class Header {
  Resolution resolution_;
  std::string header_;
  Resolution findResolution();

public:
  explicit Header(const std::string &header) {
    header_ = header;
    resolution_ = findResolution();
  };
  void setResolution(const Resolution &resolution);
  std::string getHeaderString() const { return header_; }
  Resolution getResolution() const { return resolution_; }
};

class EPSInFileStream {
  std::istream &file_;
  bool was_header_read = false;

  std::string readHeader();
  static Point readPoint(const std::string &commandLine);
  static std::string stripCommandSignature(const std::string &commandLine);
  static VariantCommand makeVariantCommand(const std::string &command_line,
                                           const std::string &command_signature);
public:
  explicit EPSInFileStream(std::istream &f) : file_(f) {}
  EPSInFileStream(EPSInFileStream&) = delete;
  EPSInFileStream& operator=(EPSInFileStream&) = delete;
  Header getHeader();
  VariantCommand getCommand();
  bool isFinished() { return file_.peek() == EOF; }
};

class EPSOutFileStream {
  std::ostream &file_;
  bool was_header_write = false;

public:
  explicit EPSOutFileStream(std::ostream &f) : file_(f) {}
  EPSOutFileStream(EPSOutFileStream&) = delete;
  EPSOutFileStream& operator=(EPSOutFileStream&) = delete;
  void putHeader(Header &header);
  void putCommand(Command &c);
};

#endif // ZPR_EPSFILETOOLS_H
