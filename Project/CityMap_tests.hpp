#ifndef __CITY_MAP_TESTS_HPP
#define __CITY_MAP_TESTS_HPP

#include "doctest.h"
#include "CityMap.hpp"
#include <sstream>
#include <iostream>

TEST_CASE("They can visit at most 5 landmarks in Stara Zagora.")
{
    CityMap stz = CityMap::readFromFile("StaraZagora.txt");
    std::list<std::string> res = stz.bestWalk();
    CHECK_EQ(Graph::uniquesCount(res), 5);
}

#endif