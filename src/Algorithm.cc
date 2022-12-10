//
// Created by kacper on 07.12.2022.
//

#include "Algorithm.h"

ProcessableGraphicVector
Algorithm::processBatch(const ProcessableGraphicVector &batch) {
  // no processing is needed
  if (batch.size() < 2)
    return batch;
  auto prevGraphicCommand = batch.at(0);
  ProcessableGraphicVector postProcessing{};

  auto differenceVisit = [](const auto &prevGraphic, const auto &nextGraphic) {
    return prevGraphic.countDifference(nextGraphic);
  };
  auto midpointVisit = [](const auto &prevGraphic, const auto &nextGraphic) {
    return prevGraphic.createMidpoint(nextGraphic);
  };
  // starting with second element of the batch we process batch elements
  for (auto iter = batch.cbegin() + 1; iter != batch.cend(); iter++) {
    double difference = std::visit(differenceVisit, prevGraphicCommand, *iter);
    if (difference <= max_difference_) {
      auto midpoint = std::visit(midpointVisit, prevGraphicCommand, *iter);
      if (midpoint)
        prevGraphicCommand = *midpoint;
    } else {
      postProcessing.push_back(prevGraphicCommand);
      prevGraphicCommand = *iter;
    }
  }
  // we push the last element of the processed batch
  postProcessing.push_back(prevGraphicCommand);
  return postProcessing;
}