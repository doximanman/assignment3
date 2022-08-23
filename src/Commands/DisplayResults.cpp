#include "DisplayResults.hpp"

#include <utility>

DisplayResults::DisplayResults(DefaultIO &dio, Classifier& cl) : Command(dio),_cl(cl){
    _description="display results";
}

void DisplayResults::execute() {
    if(_cl.wereClassified()){
        std::vector<std::string> classifications=_cl.classify();
        for(int i=0;i<classifications.size();i++){
            _dio.write(std::to_string(i+1)+"\t"+classifications[i]);
        }
    }
    else{
        _dio.write("The data isn't classified! Please use the 'classify data' command first.");
    }
    _dio.write("Done.");
}