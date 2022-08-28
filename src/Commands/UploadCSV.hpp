#ifndef SIMPLE_EXAMPLE_UPLOADCSV_HPP
#define SIMPLE_EXAMPLE_UPLOADCSV_HPP

#include "ConfusionMatrix.hpp"

class UploadCSV : public Command {
private:
    Classifier& _cl;
public:
    /**
     * @param dio IO for reading and writing.
     * @param cl the classifier instance.
     */
    UploadCSV(DefaultIO& dio, Classifier& cl);
    /**
     * Lets the user upload new train and test files.
     */
    void execute() override;
};

#endif //SIMPLE_EXAMPLE_UPLOADCSV_HPP
