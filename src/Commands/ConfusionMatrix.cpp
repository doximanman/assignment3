#include "ConfusionMatrix.hpp"

#include <utility>
#include <iostream>
#include <cmath>
#include <set>

using namespace std;
using namespace Geometry;

struct compareByRemainder{
    bool operator()(const pair<string,float>& pair1,const pair<string,float>& pair2){
        float remainder1=pair1.second-floor(pair1.second);
        float remainder2=pair2.second-floor(pair2.second);
        return remainder1>remainder2;
    }
};

ConfusionMatrix::ConfusionMatrix(DefaultIO &dio, Classifier &cl) : Command(dio), _cl(cl) {
    _description = "display algorithm confusion matrix";
}

void ConfusionMatrix::execute() {
    if(!_cl.dataReceived()){
        // data wasn't received. can't calculate percentages.
        _dio.write("printTrain file not given! Please use the '1' command to provide the file.\n");
        return;
    }
    map<string, vector<Point>> data = _cl.getData();
    // a map of the row in the percentages matrix to the type it represents.
    map<int,string> indexToType;
    int i = 0;
    for (auto &type: data) {
        indexToType[i++]=type.first;
    }
    // the matrix of percentages.
    vector<vector<int>> percentages{};
    for (auto &type: data) {
        vector<int> currentLine;
        // calculates the line and adds the values to the matrix.
        map<string, int> currentPercentages = calcType(type.first, data);
        for (auto &percent: currentPercentages) {
            currentLine.push_back(percent.second);
        }
        percentages.push_back(currentLine);
    }
    printMatrix(percentages,indexToType);
    _dio.write("printKNN Parameters: K="+to_string(_cl.getK())+" Distance="+_cl.getDistance()+"\n");
}

map<string, int> ConfusionMatrix::calcType(const std::string &type,
                                           std::map<std::string,
                                                   std::vector<Geometry::Point>> data) {
    vector<Point> points = data[type];
    // counter of how many times each type was classified.
    map<string, int> counter{};
    int numOfPoints = 0;
    for (auto &pair: data) {
        counter[pair.first] = 0;
    }
    // classifies every point and adds the classification to the counter.
    for (Point &p: points) {
        string classification= _cl.classify(p, _cl.getK());
        counter[classification]++;
        numOfPoints++;
    }

    // set of each string to its percentage. sorted by the remainder of the percentage.
    multiset<pair<string,float>,compareByRemainder> percentages;
    int sum = 0;
    for (auto &count: counter) {
        float percentage =((float) counter[count.first] / (float) numOfPoints)*(float)100.0;
        pair<string,float> currentVal{count.first,percentage};
        percentages.insert(currentVal);
        sum+=floor(percentage);
    }
    auto it=percentages.begin();
    map<string,int> result{};
    for(int i=0;i<100-sum;i++){
        result[it->first]=(int)floor(it->second)+1;
        it++;
    }
    for(; it!=percentages.end();++it){
        result[it->first]=(int)floor(it->second);
    }
    return result;
}

void ConfusionMatrix::printMatrix(const std::vector<std::vector<int>> &matrix,map<int,string> indexToType) {
    // simply prints the matrix in the format (if indexToType wasn't given then the names won't show):
    // name1  matrix[0,0]% matrix[0,1]% matrix[0,2]%
    // name2  matrix[1,0]% matrix[1,1]% matrix[1,2]%
    // name3  matrix[2,0]% matrix[2,1]% matrix[2,2]%
    //        name1        name2        name3
    bool useTypes=true;
    if(indexToType.empty()){
        useTypes=false;
    }
    string final{};
    if(useTypes){
        final.append("print\t");
        for(int i=0;i<matrix.size();i++){
            final.append(indexToType[i]+"\t");
        }
        final.pop_back();
        final.push_back('\n');
    }
    for (int j=0;j<matrix.size();j++) {
        final.append("print");
        final.append(indexToType[j]+"\t");
        for (int i: matrix[j]) {
            final.append(to_string(i) + "%\t");
        }
        if (!matrix[j].empty()) {
            final.pop_back();
            final.push_back('\n');
        }
    }
    _dio.write(final);
}