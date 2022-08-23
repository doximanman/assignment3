#include "UploadCSV.hpp"

#include <utility>
#include "../fileHandler.hpp"
#include "../CSVManagement.hpp"

using namespace std;
using namespace files;
using namespace CSV;
using namespace Geometry;

UploadCSV::UploadCSV(DefaultIO &dio, ConfusionMatrix& cm) :
        Command(dio), _cm(cm) {
    _description = "upload an unclassified csv data file";
}

void UploadCSV::execute() {
    // clears the existing points and classifications.
    _cm.clear();
    _dio.write("Please upload your local train CSV file.");
    string trainCSV = _dio.read();
    vector<Point> train = CSVManagement::getUnclassifiedData(fileHandler::getLines(trainCSV));
    // adds the new points.
    _cm.addPoints(train);
    _dio.write("Upload complete.");
    _dio.write("Please upload your local test CSV file.");
    string testCSV = _dio.read();
    vector<string> test = fileHandler::getLines(testCSV);
    // adds the new classifications.
    _cm.addClassifications(test);
    _dio.write("Upload complete.");
}