#include "ConfusionMatrix.hpp"

#include <utility>

using namespace std;
using namespace Geometry;

ConfusionMatrix::ConfusionMatrix(DefaultIO &dio, KNNInstance knn) : Command(dio),
                                                                    _knn(std::move(knn)),
                                                                    _knownClassifications(),
                                                                    _points() {
    _description="display algorithm confusion matrix";
}

void ConfusionMatrix::addClassification(const string& classification) {
    _knownClassifications.push_back(classification);
}

void ConfusionMatrix::addClassifications(const vector<string>& classifications) {
    for(const string& classification:classifications){
        addClassification(classification);
    }
}
void ConfusionMatrix::addPoint(const Point& p) {
    _points.push_back(p);
}
void ConfusionMatrix::addPoints(const std::vector<Geometry::Point>& points) {
    for(const Point& p:points){
        addPoint(p);
    }
}
void ConfusionMatrix::clear() {
    _points.clear();
    _knownClassifications.clear();
}

void ConfusionMatrix::execute() {
    // implementation needed.
}
