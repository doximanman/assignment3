#include "Point.hpp"
#include "EuclideanDistance.hpp"
#include "ChebyshevDistance.hpp"
#include "ManhattanDistance.hpp"
#include "KNearestNeighbors.hpp"
#include "fileHandler.hpp"
#include <string>
#include <iostream>
#include "CSVManagement.hpp"

using namespace std;
using namespace Geometry;
using namespace CSV;
using namespace files;


/**
 * Temporary main file to demonstrate the updated CSVManagement class.
 * @param argc
 * @param argv
 * @return int.
 */
int main(int argc, char *argv[]) {
    map<string,vector<Point>> data=CSVManagement::getClassifiedData(fileHandler::getLines("../inputFiles/classified.csv"));
    vector<Point> unclassified=CSVManagement::getUnclassifiedData(fileHandler::getLines("../inputFiles/Unclassified.csv"));

    // create 3 types of distances
    EuclideanDistance euclideanDistance{};
    ManhattanDistance manhattanDistance{};
    ChebyshevDistance chebyshevDistance{};
    cout << stoi(argv[1]) << endl;

    // creating classified output files
    fileHandler::linesToFile(KNearestNeighbors::classifyData(3,euclideanDistance,data,unclassified),"../outputFiles/euclideanOutput.csv");
    fileHandler::linesToFile(KNearestNeighbors::classifyData(3,manhattanDistance,data,unclassified),"../outputFiles/manhattanOutput.csv");
    fileHandler::linesToFile(KNearestNeighbors::classifyData(3,chebyshevDistance,data,unclassified),"../outputFiles/chebyshevOutput.csv");
}
