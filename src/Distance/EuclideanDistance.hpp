#ifndef ASS1_EUCLIDIANDISTANCE_HPP
#define ASS1_EUCLIDIANDISTANCE_HPP

#include "Distance.hpp"

namespace Geometry {
    /**
     * Has a Euclidean distance function between two points.
     */
    class EuclideanDistance : public Distance {
    public:
        /**
         * @return Euclidean distance - square root of the sum of the differences between the coordinates squared.
         */
        double distance(Point p1, Point p2) override;
        std::string name() override;
    };
}

#endif //ASS1_EUCLIDIANDISTANCE_HPP
