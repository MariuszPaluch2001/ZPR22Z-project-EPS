//
// Created by mariusz on 08.11.22.
//
#include <sstream>

#include "EPSFileTools.h"

Resolution Header::findResolution() {
  unsigned int x_res = 0;
  unsigned int y_res = 0;
  std::string line;
  std::stringstream ss(header_);
  bool is_res_found = false;
  while (std::getline(ss, line)) {
    if (line.rfind("%%BoundingBox", 0) == 0) {
      std::stringstream s(line);
      std::string tag, zero1, zero2, x, y;
      s >> tag >> zero1 >> zero2 >> x >> y;
      x_res = std::stoi(x);
      y_res = std::stoi(y);
      is_res_found = true;
    }
  }
  if (!is_res_found)
      ///not found xD - 3 forma czasownika find
    throw std::runtime_error("Resolution not founded.");
  return {x_res, y_res};
}

void Header::setResolution(const Resolution &resolution) {
  resolution_.setX(resolution.getX());
  resolution_.setY(resolution.getY());
}

std::string EPSInFileStream::readHeader() {
  std::string text;
  std::string header_buffer;
  bool is_finished_flag;
  ///lepiej na start if(was_header_read) throw ... - bardziej czytelnie
  /// potem lecisz bez else'a, bo i tak sie wykona albo to, albo dalsze
  if (!was_header_read) {
    is_finished_flag = isFinished();
    while (!is_finished_flag) {
      std::getline(file_, text);
      if (text == "%%EndComments") {
        header_buffer += "%%EndComments\n";
        break;
      }
      header_buffer += text + '\n';
      is_finished_flag = isFinished();
    }
    if (is_finished_flag)
      throw std::runtime_error("File is finished.");
  } else
    throw std::runtime_error("Header has been read.");

  was_header_read = true;
  return header_buffer;
}

Header EPSInFileStream::getHeader() {
    ///to mozna w jednej linijce - return Header(readHeader())
  std::string header_str = readHeader();
  Header header(header_str);
  return header;
}

Coordinates EPSInFileStream::readPoint(const std::string &command_line) {
  std::stringstream s(command_line);
  ///nie trzeba stod, jak zadeklarujesz x i y jako liczby, to >> potraktuje je jako liczby
  std::string x, y;
  s >> x >> y;
  return {std::stod(x), std::stod(y)};
}
std::string
EPSInFileStream::stripCommandSignature(const std::string &command_line) {
  std::string command_signature;
  std::size_t found;
  found = command_line.find_last_of(' ');
  if (found != std::string::npos)
    command_signature = command_line.substr(found + 1);
  else
    command_signature = command_line;

  return command_signature;
}

///tutaj mozna jednak wcisnac fabrykę, ale to jak chcesz
VariantCommand
EPSInFileStream::makeVariantCommand(const std::string &command_line,
                                    const std::string &command_signature) {
  if (command_signature == "l") {
    return {RightOrientedLineCommand(readPoint(command_line))};
  } else if (command_signature == "lineto") {
    return {LeftOrientedLineCommand(readPoint(command_line))};
  } else if (command_signature == "p2") {
    return {PointCommand(readPoint(command_line))};
  } else {
    return {NonProcessableCommand(command_line)};
  }
}

VariantCommand EPSInFileStream::getCommand() {
  std::string text;
  std::string command_signature;
  ///if(!was_header_read) throw ...
  if (was_header_read) {
      ///tutaj znowu - if(isFinished()) throw .. - bardziej czytelne
    if (!isFinished()) {
      std::getline(file_, text);
      command_signature = stripCommandSignature(text);
      return makeVariantCommand(text, command_signature);
    } else {
      throw std::runtime_error("File is finished.");
    }
  } else ///hasn't been read, ale to szczegół
    throw std::runtime_error("Header hasn't read yet.");
}

void EPSOutFileStream::putHeader(Header &header) {
  if (was_header_write)
    throw std::runtime_error("Header has already written.");
  ///mozna w jedna linijke mniej - bez zmiennej header_string
  std::string header_string = header.getHeaderString();
  file_ << header_string;
  was_header_write = true;
}

void EPSOutFileStream::putCommand(Command &command) {
  if (!was_header_write)
      ///hasn't been written
    throw std::runtime_error("Header hasn't written.");
  file_ << command.toString() << '\n';
}