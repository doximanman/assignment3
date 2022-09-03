#include "fileHandler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace files;
using namespace std;

std::string fileHandler::getString(const std::string& filePath,int* err) {
    if(err!=nullptr){
        *err=0;
    }
    // opens the file.
    fstream file(filePath, ios::in);
    string final{};
    string line;
    bool isEmpty=true;
    // file couldn't open.
    if(!file.is_open()&&err!=nullptr){
        *err=-1;
    }
    // adds every line to the string, seperated by '\n'.
    while(getline(file,line)){
        isEmpty=false;
        final.append(line);
        final.push_back('\n');
    }
    // removes the last \n.
    if(!isEmpty){
        final.pop_back();
    }
    return final;
}

vector<string> fileHandler::getLines(const std::string& filePath,int* err) {
    if(err!=nullptr){
        *err=0;
    }
    // opens the file.
    fstream file(filePath, ios::in);
    vector<string> final{};
    string line;
    // file couldn't open.
    if(!file.is_open()&&err!=nullptr){
        *err=-1;
    }
    // adds every line to the list.
    while(getline(file,line)){
        // removing possible '\r' chars
        if(line[line.size()-1]=='\r'){
            line.pop_back();
        }
        final.push_back(line);
    }
    return final;
}

void fileHandler::stringToFile(const std::string& data, const std::string& filePath,int* err) {
    if(err!=nullptr){
        *err=0;
    }
    // simply writes it to the file.
    ofstream writingFile(filePath);
    if(!writingFile.is_open()&&err!=nullptr){
        *err=-1;
    }
    writingFile << data << endl;
}

void fileHandler::linesToFile(const std::vector<std::string>& data, const std::string &filePath,int* err) {
    if(err!=nullptr){
        *err=0;
    }
    // writes every line to the file.
    ofstream writingFile(filePath);
    if(!writingFile.is_open()&&err!=nullptr){
        *err=-1;
    }
    for(auto &line : data){
        writingFile << line << endl;
    }
}

vector<string> fileHandler::stringToLines(const std::string &data,char separator) {
    vector<string> result{};
    stringstream str(data);
    string line;
    while(getline(str,line,separator)){
        // removes possible '\r'
        if(!line.empty()) {
            if (line[line.length() - 1] == '\r') {
                line.pop_back();
            }
            result.push_back(line);
        }
    }
    return result;
}

std::string fileHandler::linesToString(const std::vector<std::string>& lines) {
    string result{};
    for(const string& line : lines){
        result.append(line+"\n");
    }
    return result;
}

bool fileHandler::validPath(const std::string& path) {
    ofstream test(path);
    return test.is_open();
}