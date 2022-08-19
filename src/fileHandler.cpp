//
// Created by kalo3 on 18-Aug-22.
//

#include "fileHandler.hpp"
#include <iostream>
#include <fstream>

using namespace files;
using namespace std;

std::string fileHandler::getString(const std::string& filePath) {
    fstream file(filePath, ios::in);
    string final{};
    string line;
    bool isEmpty=true;
    if(!file.is_open()){
        perror("Could not open the file");
    }
    while(getline(file,line)){
        isEmpty=false;
        final.append(line);
        final.push_back('\n');
    }
    if(!isEmpty){
        final.pop_back();
    }
    return final;
}

vector<string> fileHandler::getLines(const std::string& filePath) {
    fstream file(filePath, ios::in);
    vector<string> final{};
    string line;
    if(!file.is_open()){
        perror("Could not open the file");
    }
    while(getline(file,line)){
        final.push_back(line);
    }
    return final;
}

void fileHandler::stringToFile(const std::string& data, const std::string& filePath) {
    ofstream writingFile(filePath);
    writingFile << data << endl;
}

void fileHandler::linesToFile(const std::vector<std::string>& data, const std::string &filePath) {
    ofstream writingFile(filePath);
    for(auto &line : data){
        writingFile << line << endl;
    }
}