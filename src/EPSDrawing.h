//
// Created by kacper on 10.12.2022.
// File contains drawing interface which will be used with GUI
//

#ifndef ZPR_EPSDRAWING_H
#define ZPR_EPSDRAWING_H
#include <fstream>
class EPSDrawingInterface {
public:
  virtual void drawFile(std::ifstream &) const = 0;
};
// will be implemented in next edition
class EPSDrawingAdapter : public EPSDrawingInterface {
public:
  virtual void drawFile(std::ifstream &) const {}
};

#endif // ZPR_EPSDRAWING_H
