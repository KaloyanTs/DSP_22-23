#ifndef __TRAIN_MAP_HPP
#define __TRAIN_MAP_HPP

#include "SkipList.hpp"

using word = std::string;
using words = std::vector<std::string>;

class TrainMap : public SkipList<word>
{
public:
    words shortestJourney(const words &);
};

#endif