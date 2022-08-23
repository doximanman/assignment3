//
// Created by kalo3 on 23-Aug-22.
//

#include "StandardIO.hpp"
#include <iostream>

using namespace std;

void StandardIO::write(const std::string &message) {
    cout << message <<endl;
}

std::string StandardIO::read() {
    string message;
    cin >> message;
    return message;
}