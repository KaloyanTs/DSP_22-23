#ifndef __BDZ__INTERFACE_HPP
#define __BDZ__INTERFACE_HPP

#include "TrainMap.hpp"
#include "CityMap.hpp"
#include "Box.hpp"

class BDZInterface
{
    static const std::string HELP_MSG;
    static const std::string BOX_PATH;

private:
    static void showShortestJourney(std::list<std::string> &j);
    static void showOptimalWalk(std::string &city, std::list<std::string> &w);
    static void showHelp();

public:
    static void run();
};

#endif