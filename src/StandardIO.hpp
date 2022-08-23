//
// Created by kalo3 on 23-Aug-22.
//

#ifndef SIMPLE_EXAMPLE_STANDARDIO_HPP
#define SIMPLE_EXAMPLE_STANDARDIO_HPP

#include "DefaultIO.hpp"

class StandardIO : public DefaultIO {
public:
    std::string read() override;
    void write(const std::string &message) override;
};


#endif //SIMPLE_EXAMPLE_STANDARDIO_HPP
