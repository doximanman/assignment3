#ifndef SIMPLE_EXAMPLE_DISPLAYRESULTS_HPP
#define SIMPLE_EXAMPLE_DISPLAYRESULTS_HPP

#include "Classifier.hpp"

class DisplayResults : public Command {
private:
    Classifier _cl;
public:
    DisplayResults(DefaultIO& dio,Classifier cl);
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_DISPLAYRESULTS_HPP
