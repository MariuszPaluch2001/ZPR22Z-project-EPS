//
// Created by mariusz on 08.11.22.
//
#include <sstream>

#include "EPSFileTools.hpp"

Resolution Header::findResolution(const std::string &header){
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
std::string Header::setResolutionInHeader() const{
    std::string new_header;
    std::string line;
    std::stringstream ss(header_);
    while (std::getline(ss, line)) {
        if (line.rfind("%%BoundingBox", 0) == 0) {
            std::stringstream s;
            s << "%%BoundingBox: 0 0 " << resolution_.getX() << " " << resolution_.getY();
            new_header += s.str() + '\n';
        }
        else if (line.rfind("%%DocumentMedia", 0) == 0){
            std::stringstream s;
            s << "%%DocumentMedia: special "<<resolution_.getX() <<" "<< resolution_.getY() <<" 0 () ()";
            new_header += s.str() + '\n';
        }
        else{
            new_header += line + '\n';
        }
    }
    return new_header;
}

void Header::setResolution(const Resolution &resolution) {
  resolution_.setX(resolution.getX());
  resolution_.setY(resolution.getY());
  header_ = setResolutionInHeader();
}

std::string EPSInFile::readHeader() {
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

Header EPSInFile::getHeader(){
  return Header(readHeader());
}

CoordinateValue EPSInFile::readPoint(const std::string &command_line) {
  std::stringstream s(command_line);
  double x, y;
  s >> x >> y;
  return {x, y};
}
std::string
EPSInFile::stripCommandSignature(const std::string &command_line) {
  std::string command_signature;
  std::size_t found;
  found = command_line.find_last_of(' ');
  if (found != std::string::npos)
    command_signature = command_line.substr(found + 1);
  else
    command_signature = command_line;

  return command_signature;
}

std::string
EPSInFile::getCommandLine()  {
    std::string line;
    if (!was_header_read) {
        throw std::runtime_error("Header hasn't been read yet.");
    }
    if (!isFinished()) {
        std::getline(file_, line);
    } else {
        throw std::runtime_error("File is finished.");
    }
    return line;
}

bool EPSInFile::isNextRelative() {
    std::string signature;
    long len = file_.tellg();
    signature = stripCommandSignature(getCommandLine());
    file_.seekg(len ,std::ios_base::beg);
    return signature == "l" or signature == "lineto";
}

bool EPSInFile::isNextAbsolute() {
    std::string signature;
    long len = file_.tellg();
    signature = stripCommandSignature(getCommandLine());
    file_.seekg(len ,std::ios_base::beg);
    return signature == "p2" or signature == "m";
}
bool EPSInFile::isNextUnprocessable() {
    return !isNextAbsolute() && !isNextRelative();
}

RelativeCommandVar EPSInFile::getRelativeCommandVar() {
    std::string command = getCommandLine();
    std::string signature = stripCommandSignature(command);
    if (signature == "l")
        return {RightLineCommand(readPoint(command))};
    else if (signature == "lineto")
        return {LeftLineCommand(readPoint(command))};
    else
        throw std::runtime_error("Unknown command.");
}
AbsoluteCommandVar EPSInFile::getAbsoluteCommandVar() {
    std::string command = getCommandLine();
    std::string signature = stripCommandSignature(command);
    if (signature == "p2")
        return {PointCommand(readPoint(command))};
    else if (signature == "m")
        return {MoveCommand(readPoint(command))};
    else
        throw std::runtime_error("Unknown command.");
}
NonProcessableCommand EPSInFile::getNonProcessableCommand() {
    std::string command = getCommandLine();
    return { command };
}

void EPSOutFile::putHeader(Header &header) {
  if (was_header_write)
    throw std::runtime_error("Header has already written.");

  file_ << header.getHeaderString();
  was_header_write = true;
}

void EPSOutFile::putCommand(const Command &command)  {
  if (!was_header_write)
    throw std::runtime_error("Header hasn't been written.");
  file_ << command.toString() << '\n';
}

void EPSOutFile::putCommand(const std::string &command) {
    if (!was_header_write)
        throw std::runtime_error("Header hasn't been written.");
    file_ << command << '\n';
}

