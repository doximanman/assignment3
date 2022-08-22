//
// Created by kalo3 on 20-Aug-22.
//

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
};


#endif //SIMPLE_EXAMPLE_COMMAND_HPP
