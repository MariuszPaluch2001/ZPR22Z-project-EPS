//
// Created by kacper on 07.12.2022.
// File contains class representing Algorithm
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
/*
 * Algorithm is used for processing batch of commands according to final
 * resolution of the picture
 */
class Algorithm {
private:
  double min_difference_ = 0.01;

public:
    Algorithm(double min_difference) : min_difference_(min_difference) {}
  double getMinDifference() const { return min_difference_; }
  void setMinDifference(double min_difference) { min_difference_ = min_difference >= 0 ? min_difference : min_difference_; }
  void rescaleBatch(ProcessableGraphicVector & batch, double scaling_factor) const;
  ProcessableGraphicVector processBatch(const ProcessableGraphicVector &batch) const;
};

#endif // ZPR_ALGORITHM_H
