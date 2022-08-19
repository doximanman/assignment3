//
// Created by kalo3 on 27-Jul-22.
//

#include "Point.hpp"

using namespace std;
using namespace Geometry;
Point::Point(const vector<double>& coordinates):dimension((int)coordinates.size()),_coordinates(coordinates) {
}
Point::Point(const Point &other):dimension(other.dimension),_coordinates(other._coordinates) {
}
double Point::at(int position) const{
    return _coordinates.at(position);
}

ostream& operator<<(ostream &os, const Geometry::Point &a){
    for(int i=0;i<a.dimension;i++){
        os<<a.at(i)<<"\t";
    }
}