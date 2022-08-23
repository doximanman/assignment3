#include "CLI.hpp"

#include <utility>
#include "fileHandler.hpp"
#include "Commands/UploadCSV.hpp"
#include "Commands/DisplayResults.hpp"
#include "Commands/DownloadResults.hpp"

using namespace std;
CLI::CLI(DefaultIO& dio) : _dio(dio),_commands(){
    auto *knn=new KNNInstance{dio};
    auto *classifier=new Classifier{dio, knn};
    auto *matrix=new ConfusionMatrix{dio,classifier};
    auto *display=new DisplayResults{dio,classifier};
    auto *download=new DownloadResults{dio,classifier};
    auto *uploader=new UploadCSV{dio,matrix};
    _commands.push_back(uploader);
    _commands.push_back(knn);
    _commands.push_back(classifier);
    _commands.push_back(display);
    _commands.push_back(download);
    _commands.push_back(matrix);
    allocated=true;
}
CLI::CLI(DefaultIO& dio,std::vector<Command*> commands):_dio(dio),_commands(std::move(commands)) {
}

void CLI::start() {
    bool stop=false;
    while(!stop) {
        _dio.write("Welcome to the KNN Classifier Server. Please choose an option:");
        for (int i = 0; i < _commands.size(); i++) {
            _dio.write(to_string(i + 1) + ". " + _commands[i]->description());
        }
        _dio.write(to_string(_commands.size()+1) + ". exit");
        string input = _dio.read();
        if (!isInteger(input) || stoi(input) < 1 || stoi(input) > _commands.size()+1) {
            do {
                _dio.write("Invalid choice! Please try again.");
                input = _dio.read();
            } while (!isInteger(input));
        }
        int choice = stoi(input);
        if(choice==_commands.size()+1){
            stop=true;
        }
        else{
            _commands[choice-1]->execute();
        }
    }
}

bool CLI::isInteger(const std::string& str) {
    for(const char&c : str){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}

CLI::~CLI() {
    if(allocated) {
        for (Command *c: _commands) {
            delete c;
        }
    }
}