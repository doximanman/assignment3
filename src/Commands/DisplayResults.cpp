#include "DisplayResults.hpp"

#include <utility>

DisplayResults::DisplayResults(DefaultIO &dio, Classifier &cl) : Command(dio), _cl(cl) {
    _description = "display results";
}

void DisplayResults::execute() {
    if (!_cl.wereClassified()) {
        _dio.write("printPlease classify data with 'classify data' command first!\n");
        return;
    }
    std::vector<std::string> classifications = _cl.classify();
    for (int i = 0; i < classifications.size(); i++) {
        _dio.write("print" + std::to_string(i + 1) + "\t" + classifications[i] + "\n");
    }
    _dio.write("printDone.\n");
}