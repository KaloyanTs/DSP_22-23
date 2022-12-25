#include "TrainMap.hpp"

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