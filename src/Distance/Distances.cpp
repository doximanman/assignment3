//
// Created by kalo3 on 24-Aug-22.
//

#include "Distances.hpp"

using namespace Geometry;

Distances::Distances() : EUC{}, CHE{}, MAN{} {
}

Distance &Distances::getDistance(const std::string &name) {
    if (name == "CHE") {
        return CHE;
    }
    if (name == "MAN") {
        return MAN;
    }
    return EUC;
}

bool Distances::isDistance(const std::string& name) {
    return name == "EUC" || name == "MAN" || name == "CHE";
}