#ifndef SIMPLE_EXAMPLE_CLI_HPP
#define SIMPLE_EXAMPLE_CLI_HPP

#include <vector>
#include "Commands/Command.hpp"

class CLI {
private:
    std::vector<Command*> _commands;
    DefaultIO& _dio;
public:
    /**
     * Initializes a command line interface with default settings and set of commands.
     * @param dio IO for reading and writing.
     */
    explicit CLI(DefaultIO& dio);
    /**
     * Initializes a command line interface with default settings a given set of commands.
     * @param commands set of the commands.
     * @param dio IO for reading and writing.
     */
    CLI(DefaultIO& dio,std::vector<Command*> commands);
    void start();
};


#endif //SIMPLE_EXAMPLE_CLI_HPP
