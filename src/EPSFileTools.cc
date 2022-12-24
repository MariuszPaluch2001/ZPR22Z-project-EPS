//
// Created by mariusz on 08.11.22.
//
#include <sstream>

#include "EPSFileTools.h"

Resolution Header::findResolution(const std::string &header) {
  unsigned int x_res = 0;
  unsigned int y_res = 0;
  std::string line;
  std::stringstream ss(header);
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
    throw std::runtime_error("Resolution not found.");
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
  if (was_header_read) {
      throw std::runtime_error("Header has been read.");
  }
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
  was_header_read = true;
  return header_buffer;
}

Header EPSInFileStream::getHeader() {
  return Header(readHeader());
}

CoordinateValue EPSInFileStream::readPoint(const std::string &command_line) {
  std::stringstream s(command_line);
  double x, y;
  s >> x >> y;
  return {x, y};
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
  if (!was_header_read) {
      throw std::runtime_error("Header hasn't been read yet.");
  }
  if (!isFinished()) {
      std::getline(file_, text);
      command_signature = stripCommandSignature(text);
      return makeVariantCommand(text, command_signature);
  } else {
      throw std::runtime_error("File is finished.");
  }
}

void EPSOutFileStream::putHeader(Header &header) {
  if (was_header_write)
    throw std::runtime_error("Header has already written.");

  file_ << header.getHeaderString();
  was_header_write = true;
}

void EPSOutFileStream::putCommand(Command &command) {
  if (!was_header_write)
    throw std::runtime_error("Header hasn't been written.");
  file_ << command.toString() << '\n';
}