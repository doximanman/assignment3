//
// Created by kalo3 on 23-Aug-22.
//

#ifndef SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP
#define SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP

#include "Classifier.hpp"

class ConfusionMatrix : public Command{
private:
    Classifier* _cl;
    std::vector<std::string> _knownClassifications;
public:
    ConfusionMatrix(DefaultIO& dio,Classifier* cl);
    void clear();
    void addPoints(const std::vector<Geometry::Point>& points);
    void addClassifications(const std::vector<std::string>& classifications);
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP
