#include "CLI.hpp"

#include <utility>
#include "fileHandler.hpp"
#include "Commands/UploadCSV.hpp"
#include "Commands/DisplayResults.hpp"
#include "Commands/DownloadResults.hpp"

using namespace std;
CLI::CLI(DefaultIO& dio) : _dio(dio),_commands(){
    auto *knn=new KNNInstance{dio};
    auto *classifier=new Classifier{dio, *knn};
    auto *matrix=new ConfusionMatrix{dio,*classifier};
    auto *display=new DisplayResults{dio,*classifier};
    auto *download=new DownloadResults{dio,*classifier};
    auto *uploader=new UploadCSV{dio,*classifier};
    _commands.push_back(unique_ptr<UploadCSV>(uploader));
    _commands.push_back(unique_ptr<KNNInstance>(knn));
    _commands.push_back(unique_ptr<Classifier>(classifier));
    _commands.push_back(unique_ptr<DisplayResults>(display));
    _commands.push_back(unique_ptr<DownloadResults>(download));
    _commands.push_back(unique_ptr<ConfusionMatrix>(matrix));
}
CLI::CLI(DefaultIO& dio,const std::vector<Command*>& commands):_dio(dio),_commands() {
    for(Command* cmd : commands){
        _commands.push_back(unique_ptr<Command>(cmd));
    }
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