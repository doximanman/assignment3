#include "DownloadResults.hpp"
#include "../fileHandler.hpp"
#include <utility>

DownloadResults::DownloadResults(DefaultIO &dio, Classifier cl) : Command(dio),_cl(std::move(cl)){
}

void DownloadResults::execute() {
    std::vector<std::string> lines{};
    if(_cl.wereClassified()){
        std::vector<std::string> classifications=_cl.classify();
        for(int i=0;i<classifications.size();i++){
            lines.push_back(std::to_string(i+1)+"\t"+classifications[i]);
        }
    }
    _dio.write("Please enter the path to save the file:");
    std::string path=_dio.read();
    files::fileHandler::linesToFile(lines,path);
    _dio.write("Done.");
}