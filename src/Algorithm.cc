//
// Created by kacper on 07.12.2022.
//

#include "Algorithm.h"
/*std::optional<processableGraphicVar> unpackToNoMonostate(const varGraphic & var) {
    if (std::holds_alternative<std::monostate>(var))
        return std::nullopt;
    if (std::holds_alternative<LeftOrientedLineCommand>(var))
        return std::get<LeftOrientedLineCommand>(var);
    if (std::holds_alternative<RightOrientedLineCommand>(var)
        return std::get<RightOriented
}*/
processableGraphicVector Algorithm::processBatch(const processableGraphicVector & batch) {
    if (batch.size() == 0)
        return {};
    auto prevGraphicCommand = batch.at(0);
    if (batch.size() == 1)
        return {prevGraphicCommand};
    processableGraphicVector postProcessing {};

    auto differenceVisit = [](const auto & prevGraphic, const auto & nextGraphic) {
        return prevGraphic.countDifference(nextGraphic);
    };
    auto midpointVisit = [](const auto & prevGraphic, const auto & nextGraphic) {
        return prevGraphic.createMidpoint(nextGraphic);
    };
    for (auto iter = batch.cbegin() + 1; iter != batch.cend(); iter++) {
        double difference = std::visit(differenceVisit, prevGraphicCommand, *iter);
        if (difference <= maxDifference) {
            auto midpoint = std::visit(midpointVisit, prevGraphicCommand, *iter);
            if (midpoint)
                prevGraphicCommand = *midpoint;
        }
        else {
            postProcessing.push_back(prevGraphicCommand);
            prevGraphicCommand = *iter;
        }
        if (iter + 1 == batch.cend())
            postProcessing.push_back(prevGraphicCommand);
    }
    return postProcessing;
}