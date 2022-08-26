#include "KNearestNeighbors.hpp"
#include <iostream>
#include <array>
#include <utility>

using namespace std;
using namespace Geometry;


KNearestNeighbors::KNearestNeighbors(const std::map<std::string, std::vector<Geometry::Point>> &data,
                                     int k,
                                     std::string  _distanceName) :
        _data(), _distance(std::move(_distanceName)), numOfPoints(0),_distances() {
    int typeCount = 0;
    for (auto &keyValPair: data) {
        _types[typeCount++] = keyValPair.first;
        _data.emplace_back(keyValPair.second);
        numOfPoints += (int) keyValPair.second.size();
    }
    if (k >= numOfPoints) {
        k = numOfPoints - 1;
    }
    _k = k;
}

int KNearestNeighbors::getK() const {
    return _k;
}

Geometry::Distance& KNearestNeighbors::getDistance() {
    return _distances.getDistance(_distance);
}
void KNearestNeighbors::setK(int k) {
    _k = k;
}

void KNearestNeighbors::setDistance(const std::string& name) {
    _distance=name;
}

vector<vector<double>> KNearestNeighbors::distances(const Geometry::Point& modelPoint) {
    // instantiates the distance table.
    vector<vector<double>> dists(_data.size());
    for (int i = 0; i < _data.size(); i++) {
        // instantiates the data list of this type.
        dists.at(i) = vector<double>(_data.at(i).size());
        for (int j = 0; j < _data.at(i).size(); j++) {
            // sets [i][j] of the table to be the distance between the model point and data[i][j].
            dists.at(i).at(j) = _distances.getDistance(_distance).distance(_data.at(i).at(j), modelPoint);
        }
    }
    return dists;
}

bool KNearestNeighbors::contains(vector<array<int, 2>> list, int val1, int val2) {
    for (auto &item: list) {
        if (item[0] == val1 && item[1] == val2) {
            return true;
        }
    }
    return false;
}

vector<array<int, 2>> KNearestNeighbors::firstK(const Geometry::Point& modelPoint) {
    vector<array<int, 2>> result(_k);
    for (auto item: result) {
        item[0] = -1;
        item[1] = -1;
    }
    vector<vector<double>> dists = distances(modelPoint);
    // finds the minimum K times - ignores the last findings (to make sure we get K different elements,
    // and not just the smallest element K times).
    for (int r = 0; r < _k; r++) {
        // initialized at infinity so that we're guaranteed to have a number smaller than it.
        double min = 0x7fffffffL;
        int index1 = -1;
        int index2 = -1;
        for (int i = 0; i < dists.size(); i++) {
            for (int j = 0; j < dists.at(i).size(); j++) {
                // if(distance is smaller than the minimum we found && we didn't find this point before as a minimum)
                if (dists.at(i).at(j) < min && (!contains(result, i, j))) {
                    // save the indices and minimum as the new minimum.
                    index1 = i;
                    index2 = j;
                    min = dists.at(i).at(j);
                }
            }
        }
        // the indices of the new minimum.
        result.at(r)[0] = index1;
        result.at(r)[1] = index2;
    }
    return result;
}

vector<Point> KNearestNeighbors::nearestNeighbors(const Geometry::Point& modelPoint) {
    // simply gets the indices of the nearest neighbors and returns a list of the actual points.
    vector<Point> neighbors = {};
    for (auto &index: firstK(modelPoint)) {
        neighbors.push_back(_data.at(index[0]).at(index[1]));
    }
    return neighbors;
}

string KNearestNeighbors::classify(const Geometry::Point& modelPoint) {
    // uses a counter list to count how many points of the closest K points are of each
    // data type, then finds the max of that counter list, and returns the index of it.
    // counter list.
    vector<int> counter(_data.size());
    // initializes at 0.
    for (int i = 0; i < _data.size(); i++) {
        counter.at(i) = 0;
    }
    // adds 1 for every occurrence.
    for (auto &index: firstK(modelPoint)) {
        counter.at(index[0])++;
    }
    // finds max.
    int max = -1;
    int maxType = -1;
    for (int i = 0; i < _data.size(); i++) {
        if (max < counter.at(i)) {
            max = counter.at(i);
            maxType = i;
        }
    }
    // returns the index of the max.
    return _types[maxType];
}

vector<string> KNearestNeighbors::classifyData(const vector<Point> &unclassifiedData) {
    vector<string> classifyStrings;
    for (auto &modelPoint: unclassifiedData) {
        classifyStrings.emplace_back(classify(modelPoint));
    }
    return classifyStrings;
}

void KNearestNeighbors::printNearestNeighbors(const Geometry::Point& modelPoint) {
    vector<Point> neighbors = nearestNeighbors(modelPoint);
    // uses the print implementation of Point to print all the points.
    for (const auto &item: neighbors) {
        std::cout << item;
    }
    std::cout << endl;
}