//
// Created by kacper on 07.12.2022.
// File contains class representing Algorithm
//

#ifndef ZPR_ALGORITHM_H
#define ZPR_ALGORITHM_H
#include <functional>
#include <variant>
#include <vector>
#include "GraphicCommands.h"
#include "Scalar2DRepresentation.h"


using ProcessableGraphicVar =
    std::variant<LeftOrientedLineCommand, RightOrientedLineCommand,
                 PointCommand>;
using ProcessableGraphicVector = std::vector<ProcessableGraphicVar>;
/*
 * Algorithm is used for processing batch of commands according to final resolution of the picture
 */
class Algorithm {
private:
  Resolution resolution_;
  double max_difference_ = 0;

public:
  Algorithm(const Resolution &res) : resolution_(res) {}
  void setResolution(const Resolution &res) { resolution_ = res; }
  Resolution getResolution() const { return resolution_; }
  ProcessableGraphicVector processBatch(const ProcessableGraphicVector &batch);
};

#endif // ZPR_ALGORITHM_H
