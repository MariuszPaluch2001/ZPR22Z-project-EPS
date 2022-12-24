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



using RelativeBatch = std::vector<RelativeCommand::VisitingVar>;
using AbsoluteBatch = std::vector<AbsoluteCommand::VisitingVar>;
/*
 * Algorithm is used for processing batch of commands according to final
 * resolution of the picture
 */
class Algorithm {
private:
  double min_difference_;
  double scaling_factor_;

public:
    explicit Algorithm(double min_difference, double scaling_factor=1) : min_difference_(min_difference), scaling_factor_(scaling_factor) {}
  double getMinDifference() const { return min_difference_; }
  void setMinDifference(double min_difference) { min_difference_ = min_difference >= 0 ? min_difference : min_difference_; }
  double getScalingFactor() const { return scaling_factor_; }
  void setScalingFactor(double scaling_factor) { scaling_factor_ = scaling_factor > 0 ? scaling_factor : scaling_factor_; }
  void rescaleRelativeBatch(RelativeBatch &) const;
    void rescaleAbsoluteBatch(AbsoluteBatch &) const;
  RelativeBatch processRelativeBatch(const RelativeBatch &) const;
  AbsoluteBatch processAbsoluteBatch(const AbsoluteBatch &) const;

};

#endif // ZPR_ALGORITHM_H
