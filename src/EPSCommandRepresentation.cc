//
// Created by kacper on 04.11.2022.
//
#include "EPSCommandRepresentation.h"
std::ostream &operator<<(std::ostream &os, const Command &com) {
  return os << com.toString();
}