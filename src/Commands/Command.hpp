#ifndef SIMPLE_EXAMPLE_COMMAND_HPP
#define SIMPLE_EXAMPLE_COMMAND_HPP

#include "../DefaultIO.hpp"

class Command {
protected:
    DefaultIO &_dio;
    std::string _description;
public:
    explicit Command(DefaultIO &dio);
    std::string description();
    virtual void execute()=0;
    virtual ~Command()=default;
};


#endif //SIMPLE_EXAMPLE_COMMAND_HPP
