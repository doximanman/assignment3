#include "CSVManagement.hpp"
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Geometry;
using namespace CSV;
using namespace std;

vector<vector<string>> CSVManagement::createDataVector(const vector<string> &lines) {
    vector<vector<string>> data;
    vector<string> row;
    string word;
    // separates each word in the line by ','
    for (auto &line: lines) {
        row.clear();
        stringstream str(line);

        while (getline(str, word, ','))
            row.push_back(word);
        data.push_back(row);
    }
    return data;
}

map<string, vector<Point>> CSVManagement::getClassifiedData(const vector<string> &lines) {
    int len = -1;
    map<string, vector<Point>> result{};
    // gets the points with their types in csv string form.
    vector<vector<string>> data = createDataVector(lines);
    for (vector<string> &point: data) {
        if(point.empty()){
            continue;
        }
        // all points have to be of the same dimension.
        if (len == -1) {
            len = (int) point.size();
        } else if (len != (int) point.size()) {
            perror("Some classified point has an invalid number of coordinates!");
        }
        vector<double> coords{};
        for (int i = 0; i < len - 1; i++) {
            coords.push_back(stod(point[i]));
        }
        Point currentPoint(coords);
        // type of the current point
        string type = point[len - 1];
        // creates a new type if the type doesn't exist yet.
        if (result.count(type) == 0) {
            result[type] = vector<Point>{};
        }
        // inserts the point to the set of points of the relevant type.
        result[type].push_back(currentPoint);
    }
    return result;
}

vector<Point> CSVManagement::getUnclassifiedData(const vector<string> &lines) {
    // same as "getClassifiedData" but without the type of every point.
    vector<Point> result{};
    vector<vector<string>> data = createDataVector(lines);
    int len = -1;
    for (vector<string> &point: data) {
        if(point.empty()){
            continue;
        }
        if (len == -1) {
            len = (int) point.size();
        } else if (len != (int) point.size()) {
            perror("Some unclassified point has an invalid number of coordinates!");
        }
        vector<double> coords{};
        for(int i=0;i<len;i++){
            coords.push_back(stod(point[i]));
        }
        result.emplace_back(Point{coords});
    }
    return result;
}