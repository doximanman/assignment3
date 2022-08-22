//
// Created by kalo3 on 22-Aug-22.
//

#include <sstream>
#include "KNNInstance.hpp"
#include "../ManhattanDistance.hpp"
#include "../ChebyshevDistance.hpp"
#include "../EuclideanDistance.hpp"
#include "../fileHandler.hpp"
#include "../CSVManagement.hpp"

using namespace std;
using namespace Geometry;
using namespace CSV;
using namespace files;

KNNInstance::KNNInstance(DefaultIO &dio) : Command(dio), _knn(defaultKNN()), _distances() {
    _description = "algorithm settings";
    // known distances
    EuclideanDistance EUC{};
    ManhattanDistance MAN{};
    ChebyshevDistance CHE{};
    _distances[EUC.name()] = &(EUC);
    _distances[MAN.name()] = &(MAN);
    _distances[CHE.name()] = &(CHE);
}

int KNNInstance::getK() {
    return _knn.getK();
}

void KNNInstance::setK(int K) {
    _knn.setK(K);
}

std::string KNNInstance::distance() {
    return _knn.getDistance().name();
}

KNearestNeighbors KNNInstance::defaultKNN() {
    // default data.
    map<string, vector<Point>> data = CSVManagement::getClassifiedData(
            fileHandler::getLines("../inputFiles/classified.csv"));
    // euclidean distance.
    EuclideanDistance EUC{};
    // K=5.
    return {data, 5, EUC};
}

void KNNInstance::execute() {
    _dio.write("The current KNN parameters are: K = " + to_string(getK()) + ", distance metric = " + distance());
    string currentLine = _dio.read();
    if (_dio.read() != "\n") {
        int newK = -1;
        Distance *newDistance = nullptr;
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
                if (_distances.count(words[1]) == 0) {
                    _dio.write("Invalid distance!");
                    currentLine = _dio.read();
                } else {
                    // the distance is known.
                    newDistance = _distances[words[1]];
                }
            }
        } while (newK == -1 || newDistance == nullptr);
        _knn.setK(newK);
        _knn.setDistance(*newDistance);
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