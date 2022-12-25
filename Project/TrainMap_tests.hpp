#ifndef __TRAIN_MAP_TESTS_HPP
#define __TRAIN_MAP_TESTS_HPP

#include "doctest.h"
#include "TrainMap.hpp"
#include <sstream>
#include <iostream>
#include <list>


TEST_CASE("Journey through sequence of cities.")
{
    TrainMap tm;
    std::string cities[] = {"Sofia", "Pazardzhik", "Plovdiv", "Dimitrovgrad", "StaraZagora", "NovaZagora", "Yambol", "Karnobat", "Burgas"};
    for (const std::string &s : cities)
        tm.push_back(s);
    tm.addLink(cities[0], cities[2]);
    tm.addLink(cities[2], cities[5]);
    tm.addLink(cities[3], cities[5]);
    tm.addLink(cities[4], cities[6]);
    tm.addLink(cities[5], cities[8]);

    SUBCASE("Journey through Plovdiv, StaraZagora and Yambol.")
    {
        std::list<std::string> citiesToVisit;
        citiesToVisit.push_back(cities[2]);
        citiesToVisit.push_back(cities[4]);
        citiesToVisit.push_back(cities[6]);
        std::list<std::string> p = tm.shortestJourney(citiesToVisit);
        std::ostringstream s;
        for (const std::string &city : p)
            s << city << '\n';
        CHECK_EQ(s.str(), "Sofia\nPlovdiv\nDimitrovgrad\nStaraZagora\nYambol\nKarnobat\nBurgas\n");
    }

    SUBCASE("Journey through no cities.")
    {
        std::list<std::string> citiesToVisit;
        std::list<std::string> p = tm.shortestJourney(citiesToVisit);
        std::ostringstream s;
        for (const std::string &city : p)
            s << city << '\n';
        CHECK_EQ(s.str(), "Sofia\nPlovdiv\nNovaZagora\nBurgas\n");
    }
}

#endif