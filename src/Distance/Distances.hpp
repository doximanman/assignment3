//
// Created by kalo3 on 24-Aug-22.
//

#ifndef SIMPLE_EXAMPLE_DISTANCES_HPP
#define SIMPLE_EXAMPLE_DISTANCES_HPP

#include "EuclideanDistance.hpp"
#include "ChebyshevDistance.hpp"
#include "ManhattanDistance.hpp"

namespace Geometry {
    class Distances {
    private:
        EuclideanDistance EUC;
        ManhattanDistance MAN;
        ChebyshevDistance CHE;
    public:
        Distances();
        Distance& getDistance(const std::string& name);
        static bool isDistance(const std::string& name);
    };

}

#endif //SIMPLE_EXAMPLE_DISTANCES_HPP
