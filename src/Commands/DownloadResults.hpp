#ifndef SIMPLE_EXAMPLE_DOWNLOADRESULTS_HPP
#define SIMPLE_EXAMPLE_DOWNLOADRESULTS_HPP

#include "Classifier.hpp"

class DownloadResults : public Command {
private:
    Classifier& _cl;
public:
    /**
     * @param dio IO for reading and writing.
     * @param cl Classifier instance to know the results.
     */
    DownloadResults(DefaultIO& dio,Classifier& cl);
    /**
     * If the unclassified points were classified, it sends the results to the client in a string CSV format.
     * File editing is done on the client side.
     */
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_DOWNLOADRESULTS_HPP
