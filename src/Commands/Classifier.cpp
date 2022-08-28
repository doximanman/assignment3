#include "Classifier.hpp"


using namespace std;
using namespace Geometry;

Classifier::Classifier(DefaultIO &dio, KNNInstance& knn) : Command(dio),_knn(knn),_points(),_classifications(){
    _description="classify data";
    classified=false;
}

std::vector<Geometry::Point> Classifier::points(){
    // returns a copy of the points vector.
    // so that values can't change from the outside.
    vector<Point> result=_points;
    return result;
}
void Classifier::clear() {
    _points.clear();
    _classifications.clear();
    // remembers that the data isn't classified now.
    classified=false;
}
void Classifier::addPoint(const Point &p) {
    _points.push_back(p);
}

void Classifier::updateData(const std::map<std::string, std::vector<Geometry::Point>> &newData) {
    _knn.updateData(newData);
}
bool Classifier::wereClassified() const {
    return classified;
}
std::vector<std::string> Classifier::classify() {
    if(!classified){
        // data isn't classified already. classifies it.
        _classifications.clear();
        for(Point& p : _points){
            _classifications.push_back(_knn.classify(p));
        }
        classified=true;
    }
    // copy vector so the classification vector won't change from outside.
    vector<string> cpy=_classifications;
    return cpy;
}
void Classifier::addPoints(const vector<Point> &points) {
    for(const Point& p : points){
        addPoint(p);
    }
}

void Classifier::execute() {
    classify();
    _dio.write("classifying data complete");
}