#include "Command.hpp"

std::string Command::description() {
    return _description;
}

Command::Command(DefaultIO &dio) : _dio(dio),_description("Default Command") {
}
