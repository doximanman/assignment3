#include <sstream>
#include "KNNInstance.hpp"
#include "../fileHandler.hpp"
#include "../CSVManagement.hpp"

using namespace std;
using namespace Geometry;
using namespace CSV;
using namespace files;

KNNInstance::KNNInstance(DefaultIO &dio) : Command(dio),_distances(), _knn(defaultKNN()) {
    _description = "algorithm settings";
}

int KNNInstance::getK() {
    return _knn.getK();
}

void KNNInstance::setK(int newK) {
    _knn.setK(newK);
}
std::string KNNInstance::getDistance() {
    return _knn.getDistance().name();
}

void KNNInstance::setDistance(const std::string& distanceName) {
    _knn.setDistance(distanceName);
}
void KNNInstance::updateData(const std::map<std::string, std::vector<Geometry::Point>> &newData) {
    _knn=KNearestNeighbors{newData,_knn.getK(),_knn.getDistance().name()};
}

std::map<std::string, std::vector<Geometry::Point>> KNNInstance::getData() {
    return _knn.getData();
}
KNearestNeighbors KNNInstance::defaultKNN() {
    // empty data.
    map<string, vector<Point>> data = {};
    // K=5, euclidean distance
    return {data, 5,"EUC"};
}

std::string KNNInstance::classify(const Geometry::Point& p) {
    return _knn.classify(p);
}
void KNNInstance::execute() {
    int newK = -1;
    string newDistance{};
    _dio.write("writeThe current KNN parameters are: K = " + to_string(getK()) + ", distance metric = " + getDistance()+"\n");
    string currentLine = _dio.read();
    if (!(currentLine=="empty")) {
        do {
            stringstream str(currentLine);
            vector<string> words{};
            string word;
            // gets all the arguments
            while (getline(str, word, ' ')) {
                words.push_back(word);
            }
            // must be only 2 arguments
            if (words.size() != 2) {
                _dio.write("writeIncorrect number of arguments!\n");
                currentLine = _dio.read();
            }
                // first argument (which is K) must be an integer
            else if (!isInteger(words[0])) {
                _dio.write("writeInvalid value for K!\n");
                currentLine = _dio.read();
            } else {
                int K = stoi(words[0]);
                // K must be between 1 and 10
                if (K > 10 || K < 1) {
                    _dio.write("writeInvalid value for K!\n");
                    currentLine = _dio.read();
                } else {
                    // K is valid.
                    newK = K;
                }
                // checking the second argument.
                // checks if the distance entered is a known distance.
                if (!Geometry::Distances::isDistance(words[1])) {
                    _dio.write("writeInvalid distance!\n");
                    currentLine = _dio.read();
                } else {
                    // the distance is known.
                    newDistance = words[1];
                }
            }
        } while (newK == -1 || newDistance.empty());
        _knn.setK(newK);
        _knn.setDistance(newDistance);
    }
}

bool KNNInstance::isInteger(const std::string &str) {
    // Every character of the string has to be a digit.
    for (char c: str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}