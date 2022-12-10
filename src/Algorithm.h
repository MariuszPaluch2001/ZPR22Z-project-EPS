//
// Created by kacper on 07.12.2022.
//

#ifndef ZPR_ALGORITHM_H
#define ZPR_ALGORITHM_H
#include "GraphicCommands.h"
#include "Scalar2DRepresentation.h"
#include <functional>
#include <variant>
#include <vector>

using ProcessableGraphicVar =
    std::variant<LeftOrientedLineCommand, RightOrientedLineCommand,
                 PointCommand>;
using ProcessableGraphicVector = std::vector<ProcessableGraphicVar>;

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
