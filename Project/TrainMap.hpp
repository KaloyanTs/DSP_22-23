#ifndef __TRAIN_MAP_HPP
#define __TRAIN_MAP_HPP

#include "SkipList.hpp"

using word = std::string;
using words = std::list<std::string>;

class TrainMap : public SkipList<word>
{
public:
    words shortestJourney(const words &);
};

#endif