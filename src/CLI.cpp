#include "CLI.hpp"
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
    // changes to true when the client chooses the exit option.
    bool stop=false;
    // prints the welcome message on the first try.
    bool firstTime=true;
    while(!stop) {
        if(firstTime){
            // welcome message.
            _dio.write("printWelcome to the KNN Classifier Server. Please choose an option:\n");
            firstTime=false;
        }
        else {
            // normal message.
            _dio.write("printPlease choose an option:\n");
        }
        // prints description of every command.
        for (int i = 0; i < _commands.size(); i++) {
            _dio.write("print"+to_string(i + 1) + ". " + _commands[i]->description()+"\n");
        }
        // exit option.
        _dio.write("write"+to_string(_commands.size()+1) + ". exit\n");
        // client's choice.
        string input = _dio.read();
        // must be an integer between 1 and the number of commands.
        if (!isInteger(input) || stoi(input) < 1 || stoi(input) > _commands.size()+1) {
            // asks for input until a valid choice is entered.
            do {
                _dio.write("writeInvalid choice! Please try again.\n");
                input = _dio.read();
            } while (!isInteger(input)|| stoi(input) < 1 || stoi(input) > _commands.size()+1);
        }
        // executes chosen command.
        int choice = stoi(input);
        if(choice==_commands.size()+1){
            stop=true;
            _dio.write("end");
        }
        else{
            _commands[choice-1]->execute();
        }
    }
}

bool CLI::isInteger(const std::string& str) {
    if(str.empty()){
        return false;
    }
    for(const char&c : str){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}