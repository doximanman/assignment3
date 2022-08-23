#ifndef SIMPLE_EXAMPLE_COMMAND_HPP
#define SIMPLE_EXAMPLE_COMMAND_HPP

#include "../DefaultIO.hpp"

class Command {
protected:
    DefaultIO &_dio;
    std::string _description;
public:
    /**
     * command message is "Default Command".
     * @param dio IO for reading and writing.
     */
    explicit Command(DefaultIO &dio);
    /**
     * @return the description of the command.
     */
    std::string description();
    /**
     * command execution. abstract.
     */
    virtual void execute()=0;
    /**
     * virtual destructor to be able to manage "new" instances of inheritor classes.
     */
    virtual ~Command()=default;
};


#endif //SIMPLE_EXAMPLE_COMMAND_HPP
