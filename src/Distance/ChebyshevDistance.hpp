#ifndef ASS1_CHEBISHEVDISTANCE_HPP
#define ASS1_CHEBISHEVDISTANCE_HPP
#include "Distance.hpp"
namespace Geometry {
    class ChebyshevDistance : public Distance {
        public:
        /**
         * @return Chebyshev distance - maximum difference between the coordinates of the points.
         */
            double distance(Point p1, Point p2) override;
            std::string name() override;
    };
}

#endif //ASS1_CHEBISHEVDISTANCE_HPP
