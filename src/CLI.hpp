#ifndef SIMPLE_EXAMPLE_CLI_HPP
#define SIMPLE_EXAMPLE_CLI_HPP

#include <vector>
#include "Commands/Command.hpp"

class CLI {
private:
    std::vector<Command*> _commands;
public:
    /**
     * Initializes a command line interface with default settings and set of commands.
     */
    CLI();
    /**
     * Initializes a command line interface with default settings a given set of commands.
     * @param commands set of the commands.
     */
    explicit CLI(std::vector<Command*> commands);
    void start();
};


#endif //SIMPLE_EXAMPLE_CLI_HPP
