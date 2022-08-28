#include "UploadCSV.hpp"
#include "../fileHandler.hpp"
#include "../CSVManagement.hpp"

using namespace std;
using namespace files;
using namespace CSV;
using namespace Geometry;

UploadCSV::UploadCSV(DefaultIO &dio, Classifier& cl) :
        Command(dio), _cl(cl) {
    _description = "upload an unclassified csv data file";
}

void UploadCSV::execute() {
    // clears the existing points and classifications.
    _cl.clear();
    _dio.write("Please upload your local train CSV file.");
    string trainCSV = _dio.read();
    map<string,vector<Point>> train=CSVManagement::getClassifiedData(fileHandler::getLines(trainCSV));
    // adds the new points.
    _cl.updateData(train);
    _dio.write("Upload complete.");
    _dio.write("Please upload your local test CSV file.");
    string testCSV = _dio.read();
    vector<Point> test=CSVManagement::getUnclassifiedData(fileHandler::getLines(testCSV));
    // adds the new classifications.
    _cl.addPoints(test);
    _dio.write("Upload complete.");
}