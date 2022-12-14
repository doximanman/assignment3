#ifndef ASS1_KNEARESTNEIGHBORS_HPP
#define ASS1_KNEARESTNEIGHBORS_HPP

#include "Distance/Distances.hpp"
#include <memory>
#include <array>
#include <map>

class KNearestNeighbors {
private:
    int _k;
    Geometry::Distances _distances;
    std::string _distance;
    /**
     * maps every type in the _data table to its name.
     */
    std::map<int, std::string> _types;
    /**
     * vector of Point vectors where the first dimension is the data
     * type, and the second dimension is the data of that type.
     */
    std::vector<std::vector<Geometry::Point>> _data;

    /**
     * @return the indices of the K closest points to the model point.
     */
    std::vector<std::array<int, 2>> firstK(const Geometry::Point &modelPoint);

    /**
     * @param list
     * @param value
     * @return whether value is in list.
     */
    static bool contains(std::vector<std::array<int, 2>> list, int val1, int val2);

    /**
     * total number of points in the data table.
     */
    int numOfPoints;

public:
    /**
      * Constructs the data table according to the given values.
      * @param data map of every type to a list of its points.
      * @param k the K to use in the algorithm.
      * @param distName name of the distance function.
      */
    KNearestNeighbors(const std::map<std::string, std::vector<Geometry::Point>> &data, int k, std::string distName);
/**
 * @return k of the knn algorithm
 */
    int getK() const;
    /**
     * @return distance of the knn algorithm
     */
    Geometry::Distance &getDistance();
    /**
     * sets the knn algorithm k to the one given.
     * @param k new k to use.
     */
    void setK(int k);
/**
 * sets the knn distance to the one given. must be a distance type known in the 'Distances' class.
 * @param name name of the distance.
 */
    void setDistance(const std::string &name);
/**
 * @return KNN data. map of every type to a vector of its points.
 */
    std::map<std::string, std::vector<Geometry::Point>> getData();

    /**
     * @return a table of all the distances from the point.
     */
    std::vector<std::vector<double>> distances(const Geometry::Point &modelPoint);

    /**
     * @return K nearest neighbors.
     */
    std::vector<Geometry::Point> nearestNeighbors(const Geometry::Point &modelPoint);

    /**
     * Classifies the point according to the closest K points - the
     * type that has the most points from the K points will be the classification.
     * @return the classification.
     */
    std::string classify(const Geometry::Point &modelPoint);

    /**
     * Prints the K nearest members.
     */
    void printNearestNeighbors(const Geometry::Point &modelPoint);

    /**
     * classifies every point in the vector.
     * @param unclassifiedData vector of points to classify
     * @return vector of classification (the i-th position is the classification of the i-th point)
     */
    std::vector<std::string> classifyData(const std::vector<Geometry::Point> &unclassifiedData);
    /**
     * copy operator.
     */
    KNearestNeighbors &operator=(const KNearestNeighbors &other);
};


#endif //ASS1_KNEARESTNEIGHBORS_HPP
