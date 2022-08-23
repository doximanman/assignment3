#include "Point.hpp"
#include "EuclideanDistance.hpp"
#include "ChebyshevDistance.hpp"
#include "ManhattanDistance.hpp"
#include "KNearestNeighbors.hpp"
#include "fileHandler.hpp"
#include <string>
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

    KNearestNeighbors knn(data,stoi(argv[1]),euclideanDistance);
    // creating classified output files
    fileHandler::linesToFile(knn.classifyData(unclassified),"../outputFiles/euclideanOutput.csv");
    knn.setDistance(manhattanDistance);
    fileHandler::linesToFile(knn.classifyData(unclassified),"../outputFiles/manhattanOutput.csv");
    knn.setDistance(chebyshevDistance);
    fileHandler::linesToFile(knn.classifyData(unclassified),"../outputFiles/chebyshevOutput.csv");
}
