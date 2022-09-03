#include "UploadCSV.hpp"

#include <utility>
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
    _dio.write("getFilePlease upload your local train CSV file.\n");
    string trainCSV = _dio.read();
    vector<string> lines=fileHandler::stringToLines(trainCSV);
    map<string,vector<Point>> train=CSVManagement::getClassifiedData(lines);
    //vector<string> lines=fileHandler::getLines(trainCSV);
    //map<string,vector<Point>> train=CSVManagement::getClassifiedData(lines);
    // adds the new points.
    _cl.updateData(train);
    _dio.write("printUpload complete.\n");
    _dio.write("getFilePlease upload your local test CSV file.\n");
    string testCSV = _dio.read();
    vector<Point> test=CSVManagement::getUnclassifiedData(fileHandler::stringToLines(testCSV));
    //vector<Point> test=CSVManagement::getUnclassifiedData(fileHandler::getLines(testCSV));
    // adds the new classifications.
    _cl.addPoints(test);
    _dio.write("printUpload complete.\n");
}