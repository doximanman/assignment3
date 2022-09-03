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
        std::vector<double> _coordinates;
    public:
        /**
         * @return the dimension of the point (number of coordinates).
         */
        int dimension() const;
        /**
         * constructor
         * @param coordinates given coordinates
         */
        explicit Point(const std::vector<double>& coordinates);
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
        /**
         * copy operator.
         */
        Point& operator=(const Point& other);
    };
}
/**
 * @return prints the point in the form x1 x2 ... xn
 */
std::ostream& operator<<(std::ostream &os, const Geometry::Point &a);
#endif //ASS1_POINT_HPP
