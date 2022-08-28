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
std::string KNNInstance::getDistance() {
    return _knn.getDistance().name();
}

void KNNInstance::updateData(const std::map<std::string, std::vector<Geometry::Point>> &newData) {
    _knn=KNearestNeighbors{newData,_knn.getK(),_knn.getDistance().name()};
}
KNearestNeighbors KNNInstance::defaultKNN() {
    // default data.
    map<string, vector<Point>> data = CSVManagement::getClassifiedData(
            fileHandler::getLines("../inputFiles/classified.csv"));
    // K=5, euclidean distance
    return {data, 5,"EUC"};
}

std::string KNNInstance::classify(const Geometry::Point& p) {
    return _knn.classify(p);
}

void KNNInstance::execute() {
    int newK = -1;
    string newDistance{};
    _dio.write("The current KNN parameters are: K = " + to_string(getK()) + ", distance metric = " + getDistance());
    string currentLine = _dio.read();
    if (!currentLine.empty()) {
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
                _dio.write("Incorrect number of arguments!");
                currentLine = _dio.read();
            }
                // first argument (which is K) must be an integer
            else if (!isInteger(words[0])) {
                _dio.write("Invalid value for K!");
                currentLine = _dio.read();
            } else {
                int K = stoi(words[0]);
                // K must be between 1 and 10
                if (K > 10 || K < 1) {
                    _dio.write("Invalid value for K!");
                    currentLine = _dio.read();
                } else {
                    // K is valid.
                    newK = K;
                }
                // checking the second argument.
                // checks if the distance entered is a known distance.
                if (!Geometry::Distances::isDistance(words[1])) {
                    _dio.write("Invalid distance!");
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