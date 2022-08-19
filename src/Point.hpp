//
// Created by kalo3 on 27-Jul-22.
//

#ifndef ASS1_POINT_HPP
#define ASS1_POINT_HPP

#include <ostream>
#include "vector"
namespace Geometry {
    /**
     * General, any dimensional spacial point - holds a set of coordinates and can provide
     * any of them at will.
     */
    class Point {
    private:
        /**
         * vector of doubles instead of *double,
         * easier to work with and manage.
         */
        const std::vector<double> _coordinates;
    public:
        /**
         * the dimension of the point (number of coordinates).
         */
        const int dimension;
        /**
         * constructor
         * @param coordinates given coordinates
         */
        Point(const std::vector<double>& coordinates);
        /**
         * copy constructor
         * @param other point to copy from.
         */
        Point(const Point& other);
        /**
         * @param position
         * @return the position-th coordinate of the point.
         */
        double at(int position) const;
    };
}
/**
 * @return prints the point in the form (x1,x2,...,xn)
 */
std::ostream& operator<<(std::ostream &os, const Geometry::Point &a);
#endif //ASS1_POINT_HPP
