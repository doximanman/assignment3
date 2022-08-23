#include "Point.hpp"

using namespace std;
using namespace Geometry;

Point::Point(const vector<double> &coordinates) : _coordinates(coordinates) {
}

Point::Point(const Point &other) = default;

double Point::at(int position) const {
    return _coordinates.at(position);
}

int Point::dimension() const {
    return (int) _coordinates.size();
}

Point &Point::operator=(const Point &other) {
    if (this == &other) {
        return *this;
    }
    _coordinates.clear();
    _coordinates = other._coordinates;
    return *this;
}

ostream &operator<<(ostream &os, const Geometry::Point &a) {
    for (int i = 0; i < a.dimension(); i++) {
        os << a.at(i) << "\t";
    }
}