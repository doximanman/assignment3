#ifndef SIMPLE_EXAMPLE_STANDARDIO_HPP
#define SIMPLE_EXAMPLE_STANDARDIO_HPP

#include "DefaultIO.hpp"

class StandardIO : public DefaultIO {
public:
    /**
     * reads a line from the console.
     * @return the line that was read.
     */
    std::string read() override;
    /**
     * writes a line to the console.
     * @param message the line to write.
     */
    void write(const std::string &message) override;
};


#endif //SIMPLE_EXAMPLE_STANDARDIO_HPP
