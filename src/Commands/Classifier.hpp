#ifndef SIMPLE_EXAMPLE_CLASSIFIER_HPP
#define SIMPLE_EXAMPLE_CLASSIFIER_HPP

#include "Command.hpp"
#include "KNNInstance.hpp"

class Classifier : public Command{
private:
    // knn instance for classifications.
    KNNInstance& _knn;
    // whether the data was given to the KNN algorithm.
    bool receivedData;
    // vector of unclassified points
    std::vector<Geometry::Point> _points;
    // vector of classifications of the unclassified points. _classifications[i]=classification of _points[i].
    std::vector<std::string> _classifications;
    // whether the points were classified.
    bool classified;
public:
    /**
     * @param dio IO for reading and writing.
     * @param knn* KNN instance to classify data with.
     */
    Classifier(DefaultIO &dio,KNNInstance& knn);
    /**
     * @return whether the points were classified.
     */
    bool wereClassified() const;
    /**
     * @return whether the data was received.
     */
    bool dataReceived() const;
    /**
     * @param p point to add.
     */
    void addPoint(const Geometry::Point& p);
    /**
     * @param p set of points to add.
     */
    void addPoints(const std::vector<Geometry::Point>& points);
    /**
     * changes the K of the KNN algorithm.
     * @param newK K to change to.
     */
    void setK(int newK);
    /**
     * @return K of the KNN algorithm.
     */
    int getK();
    /**
     * sets the distance in the KNN algorithm to the given distance.
     * distance name must be known in the "Distances" class.
     * @param distanceName name of the distance to set to.
     */
    void setDistance(const std::string& distanceName);
    /**
     * @return name of the distance that is used in the KNN algorithm.
     */
    std::string getDistance();
    /**
     * changes the data the KNN algorithm uses to the given data.
     * @param newData the data to change to.
     */
    void updateData(const std::map<std::string,std::vector<Geometry::Point>>& newData);
    /**
     * @return vector of the unclassified points.
     */
    std::vector<Geometry::Point> points();
    /**
     * @return map of every type to its set of points.
     */
    std::map<std::string,std::vector<Geometry::Point>> getData();
    /**
     * clears the points and classifications.
     */
    void clear();
    /**
     * classifies the given point using the KNN algorithm, with a given K.
     * @param p point to classify.
     * @param k the K to use.
     * @return the classification of the point as determined by the KNN algorithm with the given K.
     */
    std::string classify(const Geometry::Point& p,int k);
    /**
     * classifies existing points.
     * @return classification vector.
     */
    std::vector<std::string> classify();
    /**
     * classifieds the points if they were given.
     */
    void execute() override;

};


#endif //SIMPLE_EXAMPLE_CLASSIFIER_HPP
