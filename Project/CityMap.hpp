#ifndef __CITY_MAP_HPP
#define __CITY_MAP_HPP

#include "Graph.hpp"

using Landmark = std::string;

class CityMap : public Graph
{
    static Landmark start = "Railstation";

public:
    std::list<Landmark> bestWalk(unsigned limit) { return mostVerticesGivenTotalPrice(start, start, limit); }
    // todo CityMap tests
};

#endif