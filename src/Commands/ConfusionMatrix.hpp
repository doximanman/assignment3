#ifndef SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP
#define SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP

#include "Classifier.hpp"

class ConfusionMatrix : public Command {
private:
    Classifier &_cl;
    std::vector<std::string> _realClassifications;
    std::vector<std::string> _calculatedClassifications;
    int _N;
    int **_matrix;

    int successRates(std::string real, std::string classified);

    void calculateClassifications();

    void printMatrix();

    void setN();

public:
    ConfusionMatrix(DefaultIO &dio, Classifier &cl);

    void clear();

    void addPoints(const std::vector<Geometry::Point> &points);

    void addClassifications(const std::vector<std::string> &classifications);

    void execute() override;
};


#endif //SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP
