#ifndef SIMPLE_EXAMPLE_CLASSIFIER_HPP
#define SIMPLE_EXAMPLE_CLASSIFIER_HPP

#include "Command.hpp"
#include "KNNInstance.hpp"

class Classifier : public Command{
private:
    KNNInstance* _knn;
    std::vector<Geometry::Point> _points;
    std::vector<std::string> _classifications;
    bool classified;
public:
    /**
     * @param dio IO for reading and writing.
     * @param knn* KNN instance to classify data with.
     */
    Classifier(DefaultIO &dio,KNNInstance* knn);
    bool wereClassified() const;
    /**
     * @param p point to add.
     */
    void addPoint(const Geometry::Point& p);
    /**
     * @param p set of points to add.
     */
    void addPoints(const std::vector<Geometry::Point>& points);
    std::vector<Geometry::Point> points();
    /**
     * clears all data. points and classifications.
     */
    void clear();
    /**
     * classifies existing points.
     * @return classification vector.
     */
    std::vector<std::string> classify();
    void execute() override;

};


#endif //SIMPLE_EXAMPLE_CLASSIFIER_HPP
