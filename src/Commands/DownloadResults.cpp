#include "DownloadResults.hpp"
#include "../fileHandler.hpp"
#include <utility>

DownloadResults::DownloadResults(DefaultIO &dio, Classifier& cl) : Command(dio),_cl(cl){
    _description="download results";
}

void DownloadResults::execute() {
    // puts the classifications into a line vector.
    std::vector<std::string> lines{};
    if(_cl.wereClassified()){
        std::vector<std::string> classifications=_cl.classify();
        for(auto & classification : classifications){
            lines.push_back(classification);
        }
    }
    _dio.write("Please enter the path to save the file:");
    std::string path=_dio.read();
    files::fileHandler::linesToFile(lines,path+"/results.txt");
    _dio.write("Done.");
}