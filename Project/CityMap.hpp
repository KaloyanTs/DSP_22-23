#ifndef __CITY_MAP_HPP
#define __CITY_MAP_HPP

#include "Graph.hpp"

using Landmark = std::string;

class CityMap : public Graph
{
    static Landmark start;
    unsigned timeLimit;

public:
    std::list<Landmark> bestWalk() { return mostVerticesGivenTotalPrice(start, start, timeLimit); }
    static CityMap readFromFile(const std::string &);
    // todo CityMap tests
};

#endif