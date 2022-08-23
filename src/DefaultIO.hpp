#ifndef SIMPLE_EXAMPLE_DEFAULTIO_HPP
#define SIMPLE_EXAMPLE_DEFAULTIO_HPP

#include <string>

class DefaultIO {
public:
    virtual std::string read()=0;
    virtual void write(const std::string& message)=0;
};


#endif //SIMPLE_EXAMPLE_DEFAULTIO_HPP
