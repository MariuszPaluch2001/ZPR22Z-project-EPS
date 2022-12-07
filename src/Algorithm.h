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
using processableVector = std::vector<std::reference_wrapper<GraphicCommand>>;
using graphicVector = std::vector<GraphicCommand>;

class Algorithm {
private:
    Resolution res_;
public:
    Algorithm(const Resolution & res) : res_(res) {}
    void setResolution(const Resolution & res) { res_ = res; }
    Resolution getResolution() const { return res_; }

    graphicVector processBatch(const processableVector & vec);
};


#endif //ZPR_ALGORITHM_H
