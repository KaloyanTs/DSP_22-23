#include "CityMap.hpp"
#include <fstream>
#include <iostream>

std::string CityMap::start = "Railstation";
const unsigned CITY_MAX_LENGTH = 128;

std::list<Landmark> CityMap::findBestWalk(const std::string &path)
{
    CityMap cm = std::move(CityMap::readFromFile(path));
    return cm.bestWalk();
}

CityMap CityMap::readFromFile(const std::string &path)
{
    std::ifstream ifs;
    ifs.open(std::string("data\\") + path, std::ios::in);
    CityMap res;
    if (!ifs.is_open())
        return res;
    unsigned cities, edges, cost;
    ifs >> cities >> edges;
    char buf1[CITY_MAX_LENGTH];
    char buf2[CITY_MAX_LENGTH];
    for (unsigned i = 0; i < edges; ++i)
    {
        ifs.ignore();
        ifs >> buf1 >> buf2 >> cost;
        res.addEdge(buf1, buf2, cost);
    }
    ifs >> res.timeLimit;
    ifs.close();
    return res;
}