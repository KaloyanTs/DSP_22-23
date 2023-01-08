#include "TrainMap.hpp"
#include <fstream>

words TrainMap::solveShortestJourney(const std::string &mapPath, const std::string &constrainsPath)
{
    std::ifstream ifs;
    ifs.open(std::string("data\\") + mapPath);
    if (!ifs.is_open())
        throw std::runtime_error("Map not found!");
    unsigned count;
    ifs >> count;
    ifs.ignore();
    TrainMap tm;
    std::string buf1, buf2;
    for (unsigned i = 0; i < count; ++i)
    {
        ifs >> buf1;
        tm.push_back(buf1);
    }
    while (!ifs.eof())
    {
        ifs >> buf1 >> buf2;
        tm.addLink(buf1, buf2);
    }
    ifs.close();

    std::list<std::string> constrains;
    ifs.open(std::string("data\\") + constrainsPath);
    if (ifs.is_open())
    {
        while (!ifs.eof())
        {
            ifs >> buf1;
            constrains.push_back(buf1);
        }
        ifs.close();
    }
    return tm.shortestJourney(constrains);
}

words TrainMap::shortestJourney(const words &cities)
{
    typename words::const_iterator i = cities.begin();
    words res;
    words current;
    const std::string *from, *to;
    while (true)
    {
        if (i == cities.begin())
        {
            from = &(begin->data);
            to = (i == cities.end() ? &(end->data) : &(*i));
        }
        else if (i == cities.end())
        {
            from = &(*(--i));
            ++i;
            to = &(end->data);
        }
        else
        {
            from = &(*(--i));
            ++i;
            to = &(*i);
        }
        current = BFSpath(*from, *to);
        if (current.empty())
            return words();
        res.insert(res.end(), current.begin(), --current.end());
        if (i == cities.end())
            break;
        ++i;
    }

    res.push_back(this->end->data);
    return res;
}