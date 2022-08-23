#include "CLI.hpp"

#include <utility>
#include "fileHandler.hpp"

using namespace std;
CLI::CLI(DefaultIO& dio) : _dio(dio),_commands(){
}
CLI::CLI(DefaultIO& dio,std::vector<Command*> commands):_dio(dio),_commands(std::move(commands)) {
}


