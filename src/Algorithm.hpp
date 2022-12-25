//
// Created by kacper on 07.12.2022.
// File contains class representing Algorithm
//

#ifndef ZPR_ALGORITHM_HPP
#define ZPR_ALGORITHM_HPP
#include "GraphicCommands.h"
#include "Scalar2DRepresentation.h"
#include <functional>
#include <variant>
#include <vector>



using RelativeBatch = std::vector<RelativeCommandVar>;
using AbsoluteBatch = std::vector<AbsoluteCommandVar>;
/*
 * Algorithm is used for processing batch of commands according to final
 * resolution of the picture
 */


class Algorithm {
private:
  double min_difference_;
  double scaling_factor_;
  unsigned sorting_range_;
public:
    explicit Algorithm(double min_difference, double scaling_factor=1, unsigned sorting_range=10) : min_difference_(min_difference), scaling_factor_(scaling_factor), sorting_range_(10) {}
  double getMinDifference() const { return min_difference_; }
  void setMinDifference(double min_difference) { min_difference_ = min_difference >= 0 ? min_difference : min_difference_; }
  double getScalingFactor() const { return scaling_factor_; }
  void setScalingFactor(double scaling_factor) { scaling_factor_ = scaling_factor > 0 ? scaling_factor : scaling_factor_; }
  unsigned getSortingRange() const { return sorting_range_; }
  void setSortingRange(unsigned sorting_range) { sorting_range_ = sorting_range; }
    template <typename T> void rescaleBatch(T&) const;
    template <typename T> T processBatch(const T&) const;
    template <typename T> void sortBatch(T&) const;

};

static auto rescaleVisit = [](double scaling_factor) {
    return [scaling_factor](auto &graphic) {
        graphic.rescale(scaling_factor);
    };
};

static auto differenceVisit = [](const auto &prevGraphic, const auto &nextGraphic) {
    return countDifference(prevGraphic, nextGraphic);
};
static auto midpointVisit = [](const auto &prevGraphic, const auto &nextGraphic) {
    return createMidpoint(prevGraphic, nextGraphic);
};



template <typename T>
void Algorithm::rescaleBatch(T& batch) const {
    for (auto & graphic : batch)
        std::visit(rescaleVisit(scaling_factor_), graphic);
}

template <typename T>
T Algorithm::processBatch(const T& batch) const {
    // no processing is needed
    if (batch.size() < 2)
        return batch;
    auto prev_graphic_command = batch.at(0);
    T post_processing{};


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
template <typename T>
void Algorithm::sortBatch(T & batch) const {
    for (int i = 0; i + sorting_range_ <= batch.size(); i+=sorting_range_) {
        auto working_element = batch.at(i);
        auto stopping = batch.begin() + 1 + i + sorting_range_;
        for (auto iter = batch.begin() + 1 + i; iter != stopping; iter++) {
            auto minimal = std::min_element(iter, stopping, [&working_element](auto & a, auto & b){
                return std::visit(differenceVisit, working_element, a) < std::visit(differenceVisit, working_element, b);});
            std::iter_swap(iter, minimal);
            working_element = *iter;
        }
    }
}
#endif // ZPR_ALGORITHM_HPP
