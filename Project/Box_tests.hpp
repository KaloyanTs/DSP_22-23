#ifndef __BOX_TESTS_HPP
#define __BOX_TESTS_HPP

#include "doctest.h"
#include "Box.hpp"
#include <iostream>

TEST_CASE("Printing a Box")
{
    std::list<Box> l = Box::readFromFile("boxesdata.txt");
    for (const Box &b : l)
        std::clog << b;
    CHECK(false);
}

#endif