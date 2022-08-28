#include "ConfusionMatrix.hpp"

#include <utility>

ConfusionMatrix::ConfusionMatrix(DefaultIO &dio, Classifier &cl) : Command(dio), _cl(cl) {
    _description = "display algorithm confusion matrix";
}

void ConfusionMatrix::clear() {
    _cl.clear();
    _realClassifications.clear();
}

void ConfusionMatrix::addPoints(const std::vector<Geometry::Point> &points) {
    _cl.addPoints(points);
}

void ConfusionMatrix::setN() {
    std::vector<std::string> typesNames;
    for(std::string &classification: _realClassifications) {
    }
}

void ConfusionMatrix::addClassifications(const std::vector<std::string> &classifications) {
    for (const std::string &classification: classifications) {
        _realClassifications.push_back(classification);
    }
}

void ConfusionMatrix::calculateClassifications() {

}

void ConfusionMatrix::printMatrix() {

}

void ConfusionMatrix::execute() {
    // implementation needed.
    // code should fail if points haven't been classified yet (using the '3' command).
}