#include "ConfusionMatrix.hpp"

#include <utility>

ConfusionMatrix::ConfusionMatrix(DefaultIO &dio, Classifier& cl) : Command(dio),_cl(cl) {
    _description="display algorithm confusion matrix";
}

void ConfusionMatrix::clear() {
    _cl.clear();
    _knownClassifications.clear();
}

void ConfusionMatrix::addPoints(const std::vector<Geometry::Point>& points) {
    _cl.addPoints(points);
}

void ConfusionMatrix::addClassifications(const std::vector<std::string>& classifications) {
    for(const std::string& classification : classifications){
        _knownClassifications.push_back(classification);
    }
}
void ConfusionMatrix::execute() {
    // implementation needed.
    // code should fail if points haven't been classified yet (using the '3' command).
}