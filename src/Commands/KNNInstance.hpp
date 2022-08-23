#ifndef SIMPLE_EXAMPLE_KNNINSTANCE_HPP
#define SIMPLE_EXAMPLE_KNNINSTANCE_HPP

#include "Command.hpp"
#include "../KNearestNeighbors.hpp"

class KNNInstance : public Command{
private:
    std::map<std::string,Geometry::Distance*> _distances;
    KNearestNeighbors _knn;
    /**
     * @return default settings with K=5 and euclidean distance.
     */
    static KNearestNeighbors defaultKNN();
    /**
     * @param str a string.
     * @return whether str is an integer or not.
     */
    static bool isInteger(const std::string& str);
public:
    /**
     * Creates a new KNN instance with default parameters.
     * @param dio IO to read and write.
     */
    explicit KNNInstance(DefaultIO &dio);
    /**
     * @return the K of the KNN algorithm
     */
    int getK();
    /**
     * @return name of the KNN distance.
     */
    std::string getDistance();
    std::string classify(const Geometry::Point& p);
    /**
     * Asks the user to provide new KNN parameters.
     * If the user presses the enter key without new parameters, then nothing changes.
     * Otherwise, the user needs to provide them in the form: "K XYZ" where K is an integer between 1 and 10, and
     *                                                        "XYZ" is the name of the distance to use.
     */
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_KNNINSTANCE_HPP
