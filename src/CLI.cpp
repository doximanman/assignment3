//
// Created by kalo3 on 20-Aug-22.
//

#include "CLI.hpp"

#include <utility>
#include "fileHandler.hpp"

using namespace std;
CLI::CLI() : _commands(){
}
CLI::CLI(std::vector<Command *> commands):_commands(std::move(commands)) {
}


