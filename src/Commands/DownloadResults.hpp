#ifndef SIMPLE_EXAMPLE_DOWNLOADRESULTS_HPP
#define SIMPLE_EXAMPLE_DOWNLOADRESULTS_HPP

#include "Classifier.hpp"

class DownloadResults : public Command {
private:
    Classifier* _cl;
public:
    DownloadResults(DefaultIO& dio,Classifier* cl);
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_DOWNLOADRESULTS_HPP
