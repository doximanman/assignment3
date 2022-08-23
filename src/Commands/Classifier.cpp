//
// Created by kalo3 on 23-Aug-22.
//

#include "Classifier.hpp"

using namespace std;
using namespace Geometry;

Classifier::Classifier(DefaultIO &dio, KNNInstance knn) : Command(dio),_knn(std::move(knn)),_points(),_classifications(){
    _description="classify data";
}

std::vector<Geometry::Point> Classifier::points(){
    // returns a copy of the points vector.
    // so that values can't change from the outside.
    vector<Point> result=_points;
    return result;
}
void Classifier::clear() {
    _points.clear();
}
void Classifier::addPoint(const Point &p) {
    _points.push_back(p);
}

bool Classifier::wereClassified() {
    return _classifications.size()==_points.size();
}
std::vector<std::string> Classifier::classify() {
    if(_classifications.size()!=_points.size()){
        _classifications.clear();
        for(Point& p : _points){
            _classifications.push_back(_knn.classify(p));
        }
    }
    return _classifications;
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