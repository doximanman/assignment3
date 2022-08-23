#ifndef SIMPLE_EXAMPLE_DISPLAYRESULTS_HPP
#define SIMPLE_EXAMPLE_DISPLAYRESULTS_HPP

#include "Classifier.hpp"

class DisplayResults : public Command {
private:
    Classifier& _cl;
public:
    /**
     * @param dio IO for reading and writing.
     * @param cl classifier to know the results.
     */
    DisplayResults(DefaultIO& dio,Classifier& cl);
    /**
     * prints the results to the IO.
     */
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_DISPLAYRESULTS_HPP
