//
// Created by kalo3 on 20-Aug-22.
//

#ifndef SIMPLE_EXAMPLE_UPLOADCSV_HPP
#define SIMPLE_EXAMPLE_UPLOADCSV_HPP

#include "ConfusionMatrix.hpp"

class UploadCSV : public Command {
private:
    ConfusionMatrix _cm;
public:
    /**
     * @param dio IO for reading and writing.
     * @param cm the confusion matrix that stores the points and known classifications.
     */
    UploadCSV(DefaultIO& dio, ConfusionMatrix cm);
    /**
     * Lets the user upload new train and test files.
     */
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_UPLOADCSV_HPP
