//
// Created by kalo3 on 22-Aug-22.
//

#ifndef SIMPLE_EXAMPLE_KNNINSTANCE_HPP
#define SIMPLE_EXAMPLE_KNNINSTANCE_HPP

#include "Command.hpp"
#include "../KNearestNeighbors.hpp"

class KNNInstance : public Command{
private:
    std::map<std::string,Geometry::Distance*> _distances;
    KNearestNeighbors _knn;
    static KNearestNeighbors defaultKNN();
    static bool isInteger(const std::string& str);
public:
    /**
     * Creates a new KNN instance with default parameters.
     * @param dio IO to read and write.
     */
    explicit KNNInstance(DefaultIO &dio);
    int getK();
    void setK(int K);
    std::string distance();
    void execute() override;
};


#endif //SIMPLE_EXAMPLE_KNNINSTANCE_HPP
