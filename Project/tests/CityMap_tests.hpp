#ifndef __CITY_MAP_TESTS_HPP
#define __CITY_MAP_TESTS_HPP

#include "doctest.h"
#include "../CityMap.hpp"
#include <sstream>
#include <iostream>

TEST_CASE("They can visit at most 5 landmarks in Stara Zagora.")
{
    std::list<std::string> res = CityMap::findBestWalk("StaraZagora.txt");
    for (const std::string &city : res)
        std::clog << city << '\n';
    CHECK_EQ(Graph::uniquesCount(res), 5);
}

TEST_CASE("They can not visit only the Center in Yambol.")
{
    std::list<std::string> res = CityMap::findBestWalk("Yambol.txt");
    for (const std::string &city : res)
        CHECK_NE(city, "Center");
    CHECK_EQ(Graph::uniquesCount(res), 3);
}

#endif