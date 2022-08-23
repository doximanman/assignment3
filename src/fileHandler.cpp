//
// Created by kalo3 on 18-Aug-22.
//

#include "fileHandler.hpp"
#include <iostream>
#include <fstream>

using namespace files;
using namespace std;

std::string fileHandler::getString(const std::string& filePath) {
    // opens the file.
    fstream file(filePath, ios::in);
    string final{};
    string line;
    bool isEmpty=true;
    // file couldn't open.
    if(!file.is_open()){
        perror("Could not open the file");
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

vector<string> fileHandler::getLines(const std::string& filePath) {
    // opens the file.
    fstream file(filePath, ios::in);
    vector<string> final{};
    string line;
    // file couldn't open.
    if(!file.is_open()){
        perror("Could not open the file");
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

void fileHandler::stringToFile(const std::string& data, const std::string& filePath) {
    // simply writes it to the file.
    ofstream writingFile(filePath);
    writingFile << data << endl;
}

void fileHandler::linesToFile(const std::vector<std::string>& data, const std::string &filePath) {
    // writes every line to the file.
    ofstream writingFile(filePath);
    for(auto &line : data){
        writingFile << line << endl;
    }
}