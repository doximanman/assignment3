#include "DownloadResults.hpp"
#include "../fileHandler.hpp"
#include <utility>

DownloadResults::DownloadResults(DefaultIO &dio, Classifier &cl) : Command(dio), _cl(cl) {
    _description = "download results";
}

void DownloadResults::execute() {
    if (!_cl.wereClassified()) {
        _dio.write("printPlease classify data with 'classify data' command first!\n");
        return;
    }
    // puts the classifications into one string. Lines seperated by '@'.
    std::string message;
    std::vector<std::string> classifications = _cl.classify();
    for (auto &classification: classifications) {
        message.append(classification + "@");
    }
    _dio.write("toFilePlease enter the path to save the file:\n" + message+"\n");
    _dio.write("Done.\n");
}