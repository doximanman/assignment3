#include "Classifier.hpp"


using namespace std;
using namespace Geometry;

Classifier::Classifier(DefaultIO &dio, KNNInstance &knn) : Command(dio), _knn(knn), _points(), _classifications(),
                                                           receivedData(false) {
    _description = "classify data";
    classified = false;
}

std::vector<Geometry::Point> Classifier::points() {
    // returns a copy of the points vector.
    // so that values can't change from the outside.
    vector<Point> result = _points;
    return result;
}

void Classifier::clear() {
    _points.clear();
    _classifications.clear();
    // remembers that the data isn't classified now.
    classified = false;
}

void Classifier::addPoint(const Point &p) {
    _points.push_back(p);
}

int Classifier::getK() {
    return _knn.getK();
}

void Classifier::setK(int newK) {
    _knn.setK(newK);
}

std::string Classifier::getDistance() {
    return _knn.getDistance();
}

void Classifier::setDistance(const std::string &distanceName) {
    _knn.setDistance(distanceName);
}

void Classifier::updateData(const std::map<std::string, std::vector<Geometry::Point>> &newData) {
    _knn.updateData(newData);
    receivedData = true;
    classified=false;
    _classifications.clear();
}

bool Classifier::wereClassified() const {
    return classified;
}

bool Classifier::dataReceived() const {
    return receivedData;
}
std::map<std::string, std::vector<Geometry::Point>> Classifier::getData() {
    return _knn.getData();
}

std::string Classifier::classify(const Geometry::Point &p, int k) {
    if (!receivedData) {
        _dio.write("printPlease upload files with 'upload an unclassified csv data file' command first!\n");
        return {};
    }
    int originalK = getK();
    setK(k);
    string result = _knn.classify(p);
    setK(originalK);
    return result;
}

std::vector<std::string> Classifier::classify() {
    if (!receivedData) {
        // data wasn't received yet, so classifying is meaningless.
        _dio.write("printPlease upload files with 'upload an unclassified csv data file' command first!\n");
        return {};
    }
    if (!classified) {
        // data isn't classified already. classifies it.
        _classifications.clear();
        for (Point &p: _points) {
            _classifications.push_back(_knn.classify(p));
        }
        classified = true;
    }
    // copy vector so the classification vector won't change from outside the instance.
    vector<string> cpy = _classifications;
    return cpy;
}

void Classifier::addPoints(const vector<Point> &points) {
    for (const Point &p: points) {
        addPoint(p);
    }
}

void Classifier::execute() {
    classify();
    if (receivedData) {
        _dio.write("printclassifying data complete\n");
    }
}