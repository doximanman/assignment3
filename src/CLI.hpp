#ifndef SIMPLE_EXAMPLE_CLI_HPP
#define SIMPLE_EXAMPLE_CLI_HPP

#include <vector>
#include <memory>
#include "Commands/Command.hpp"

class CLI {
private:
    bool allocated=false;
    std::vector<Command*> _commands;
    DefaultIO& _dio;
    static bool isInteger(const std::string& str);
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
    ~CLI();
};


#endif //SIMPLE_EXAMPLE_CLI_HPP
