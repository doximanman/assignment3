#ifndef SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP
#define SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP

#include "Classifier.hpp"

class ConfusionMatrix : public Command {
private:
    // classifier instance, to be able to get the data, and to classify points.
    Classifier &_cl;
    /**
     * prints the matrix to the IO.
     * @param matrix matrix to print.
     * @param indexToType optional names for the rows and columns.
     */
    void printMatrix(const std::vector<std::vector<int>>& matrix,std::map<int,std::string> indexToType={});
    /**
     * classifies each point in the data of the given type, and calculates the accuracy of the algorithm.
     * @param type name of the type.
     * @param data the data that has known types and the points of each type.
     * @return map of every type to how many points out of data[type] (in percentages) were identified as that type.
     */
    std::map<std::string,int> calcType(const std::string& type,std::map<std::string,std::vector<Geometry::Point>> data);
public:
    /**
     * @param dio IO for reading and writing.
     * @param cl classifier instance for data and classification capabilities.
     */
    ConfusionMatrix(DefaultIO &dio, Classifier &cl);
    /**
     * calculates a confusion matrix according to the data:
     * a matrix of size NxN where N is the number of types,
     * and position (i,j) is how many of type i were identified using the KNN algorithm as type j (in percentages).
     */
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP
