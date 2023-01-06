#ifndef __TRAIN_MAP_TESTS_HPP
#define __TRAIN_MAP_TESTS_HPP

#include "doctest.h"
#include "../TrainMap.hpp"
#include <sstream>
#include <iostream>
#include <list>

TEST_CASE("Journey through sequence of cities.")
{
    SUBCASE("Journey through Plovdiv, StaraZagora and Yambol.")
    {
        std::list<std::string> res = TrainMap::solveShortestJourney("SofiaBurgas.txt", "AnyaVanko.txt");
        std::ostringstream s;
        for (const std::string &city : res)
            s << city << '\n';
        CHECK_EQ(s.str(), "Sofia\nPlovdiv\nDimitrovgrad\nStaraZagora\nYambol\nKarnobat\nBurgas\n");
    }

    SUBCASE("Journey through no cities.")
    {
        std::list<std::string> res = TrainMap::solveShortestJourney("SofiaBurgas.txt", "test2.txt");
        std::ostringstream s;
        for (const std::string &city : res)
            s << city << '\n';
        CHECK_EQ(s.str(), "Sofia\nPlovdiv\nNovaZagora\nBurgas\n");
    }
}

#endif