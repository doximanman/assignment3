//
// Created by kalo3 on 23-Aug-22.
//

#include "DisplayResults.hpp"

#include <utility>

DisplayResults::DisplayResults(DefaultIO &dio, Classifier cl) : Command(dio),_cl(std::move(cl)){
    _description="display results";
}

void DisplayResults::execute() {
    if(_cl.wereClassified()){
        std::vector<std::string> classifications=_cl.classify();
        for(int i=0;i<classifications.size();i++){
            _dio.write(std::to_string(i+1)+"\t"+classifications[i]);
        }
    }
    _dio.write("Done.");
}