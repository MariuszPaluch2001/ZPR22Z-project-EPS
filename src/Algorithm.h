//
// Created by kacper on 07.12.2022.
//

#ifndef ZPR_ALGORITHM_H
#define ZPR_ALGORITHM_H
#include "Scalar2DRepresentation.h"
#include "GraphicCommands.h"
#include <vector>
#include <variant>
#include <functional>
using processableGraphicVar = std::variant<LeftOrientedLineCommand, RightOrientedLineCommand, PointCommand>;
using processableGraphicVector = std::vector<processableGraphicVar>;

class Algorithm {
private:
    Resolution res_;
    double maxDifference = 0;
public:
    Algorithm(const Resolution & res) : res_(res) {}
    void setResolution(const Resolution & res) { res_ = res; }
    Resolution getResolution() const { return res_; }
    processableGraphicVector processBatch(const processableGraphicVector & batch);
};


#endif //ZPR_ALGORITHM_H
