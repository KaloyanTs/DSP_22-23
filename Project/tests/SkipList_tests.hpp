#ifndef __SKIPLIST_TESTS_HPP
#define __SKIPLIST_TESTS_HPP

#include "doctest.h"
#include "../SkipList.hpp"
#include <sstream>
#include <string>
#include <queue>
#include <iostream>

using IntList = SkipList<int>;

TEST_CASE("Creating empty SkipList is indeed empty")
{
    IntList l;
    CHECK(l.empty());
}

TEST_CASE("Constructor with one parameters cretes non-empty SkipList")
{
    IntList l(1);
    CHECK_FALSE(l.empty());
}

TEST_CASE("Принтиране на SkipList")
{
    IntList l(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.addLink(2, 4);
    l.addLink(1, 5);
    std::ostringstream s;
    s << l;
    CHECK_EQ(s.str(), "1 (link to 5)\n2 (link to 4)\n3\n4\n5");
}

TEST_CASE("Копирането на SkipList е коректно")
{
    IntList l1(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.addLink(2, 4);
    l1.addLink(1, 5);
    std::ostringstream s1;
    s1 << l1;
    IntList l2(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(4);
    l2.push_back(5);
    l2.addLink(2, 4);
    l2.addLink(1, 5);
    std::ostringstream s2;
    s2 << l2;
    CHECK_EQ(s1.str(), s2.str());
    l2.push_back(6);
    s2.clear();
    s2 << l2;
    CHECK_NE(s1.str(), s2.str());
}

TEST_CASE("Adding element indeed works.")
{
    IntList l;
    l.push_back(2);
    CHECK_FALSE(l.empty());
}

#endif