//
// Created by kalo3 on 23-Aug-22.
//

#ifndef SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP
#define SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP

#include "KNNInstance.hpp"

class ConfusionMatrix : public Command{
private:
    KNNInstance _knn;
    std::vector<Geometry::Point> _points;
    std::vector<std::string> _knownClassifications;
public:
    /**
     * @param dio IO for reading and writing.
     * @param knn KNN instance to classify data with.
     */
    ConfusionMatrix(DefaultIO &dio,KNNInstance knn);
    /**
     * @param p point to add.
     */
    void addPoint(const Geometry::Point& p);
    /**
     * @param p set of points to add.
     */
    void addPoints(const std::vector<Geometry::Point>& points);
    /**
     * @param classification classification to add.
     */
    void addClassification(const std::string& classification);
    /**
     * @param classifications set of classifications to add.
     */
    void addClassifications(const std::vector<std::string>& classifications);
    /**
     * clears all data. points and classifications.
     */
    void clear();
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_CONFUSIONMATRIX_HPP
