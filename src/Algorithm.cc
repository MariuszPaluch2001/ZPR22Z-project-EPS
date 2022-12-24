//
// Created by kacper on 07.12.2022.
//

#include "Algorithm.h"


RelativeBatch
Algorithm::processRelativeBatch(const RelativeBatch &batch) const {
    static auto differenceVisit = [](const auto &prevGraphic, const auto &nextGraphic) {
        return prevGraphic.countDifference(nextGraphic);
    };
    static auto midpointVisit = [](const auto &prevGraphic, const auto &nextGraphic) {
        return prevGraphic.createMidpoint(nextGraphic);
    };
// no processing is needed
if (batch.size() < 2)
  return batch;
auto prev_graphic_command = batch.at(0);
    RelativeBatch post_processing{};


// starting with second element of the batch we process batch elements
for (auto iter = batch.cbegin() + 1; iter != batch.cend(); iter++) {
  double difference = std::visit(differenceVisit, prev_graphic_command, *iter);
  if (difference <= min_difference_)
      prev_graphic_command = std::visit(midpointVisit, prev_graphic_command, *iter);
  else {
    post_processing.push_back(prev_graphic_command);
    prev_graphic_command = *iter;
  }
}
// we push the last element of the processed batch
post_processing.push_back(prev_graphic_command);
return post_processing;

}

AbsoluteBatch
Algorithm::processAbsoluteBatch(const AbsoluteBatch &batch) const {
    ///@todo change it, so it searches for closest ones
    static auto differenceVisit = [](const auto &prevGraphic, const auto &nextGraphic) {
        return prevGraphic.countDifference(nextGraphic);
    };
    static auto midpointVisit = [](const auto &prevGraphic, const auto &nextGraphic) {
        return prevGraphic.createMidpoint(nextGraphic);
    };
// no processing is needed
    if (batch.size() < 2)
        return batch;
    auto prev_graphic_command = batch.at(0);
    AbsoluteBatch post_processing{};


// starting with second element of the batch we process batch elements
    for (auto iter = batch.cbegin() + 1; iter != batch.cend(); iter++) {
        double difference = std::visit(differenceVisit, prev_graphic_command, *iter);
        if (difference <= min_difference_)
            prev_graphic_command = std::visit(midpointVisit, prev_graphic_command, *iter);
        else {
            post_processing.push_back(prev_graphic_command);
            prev_graphic_command = *iter;
        }
    }
// we push the last element of the processed batch
    post_processing.push_back(prev_graphic_command);
    return post_processing;

}

void Algorithm::rescaleAbsoluteBatch(AbsoluteBatch & batch) const {
    static auto rescaleVisit = [this](auto & graphic) {
        graphic.rescale(scaling_factor_);
    };
    for (auto & graphic : batch)
        std::visit(rescaleVisit, graphic);
}

void Algorithm::rescaleRelativeBatch(RelativeBatch & batch) const {
    static auto rescaleVisit = [this](auto & graphic) {
        graphic.rescale(scaling_factor_);
    };
    for (auto & graphic : batch)
        std::visit(rescaleVisit, graphic);
}
