//
// Created by kacper on 07.12.2022.
//

#include "Algorithm.h"

ProcessableGraphicVector
Algorithm::processBatch(const ProcessableGraphicVector &batch) const {
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
ProcessableGraphicVector post_processing{};


// starting with second element of the batch we process batch elements
for (auto iter = batch.cbegin() + 1; iter != batch.cend(); iter++) {
  double difference = std::visit(differenceVisit, prev_graphic_command, *iter);
  if (difference <= max_difference_)
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


void Algorithm::rescaleBatch(ProcessableGraphicVector & batch, double scaling_factor) const {
    static auto rescaleVisit = [&scaling_factor](auto & graphic) {
        graphic.rescale(scaling_factor);
    };
    for (auto & graphic : batch)
        std::visit(rescaleVisit, graphic);
}
