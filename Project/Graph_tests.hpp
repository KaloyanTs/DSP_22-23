#ifndef __GRAPH_TESTS_HPP
#define __GRAPH_TESTS_HPP

#include "doctest.h"
#include "Graph.hpp"
#include <sstream>
#include <iostream>

TEST_CASE("Creating empty Graph is indeed empty")
{
    Graph g;
    CHECK(g.empty());
}

TEST_CASE("Constructor with one parameters cretes non-empty Graph")
{
    CHECK(false);
    // todo repair
    // Graph l(1);
    // CHECK_FALSE(l.empty());
}

TEST_CASE("Принтиране на Graph")
{
    CHECK(false);
    // todo repair

    // IntList l(1);
    // l.push_back(2);
    // l.push_back(3);
    // l.push_back(4);
    // l.push_back(5);
    // l.addLink(2, 4);
    // l.addLink(1, 5);
    // std::ostringstream s;
    // s << l;
    // CHECK_EQ(s.str(), "1 (link to 5)\n2 (link to 4)\n3\n4\n5");
}

TEST_CASE("Копирането на Graph е коректно")
{
    CHECK(false);
    // todo repair

    // IntList l1(1);
    // l1.push_back(2);
    // l1.push_back(3);
    // l1.push_back(4);
    // l1.push_back(5);
    // l1.addLink(2, 4);
    // l1.addLink(1, 5);
    // std::ostringstream s1;
    // s1 << l1;
    // IntList l2(1);
    // l2.push_back(2);
    // l2.push_back(3);
    // l2.push_back(4);
    // l2.push_back(5);
    // l2.addLink(2, 4);
    // l2.addLink(1, 5);
    // std::ostringstream s2;
    // s2 << l2;
    // CHECK_EQ(s1.str(), s2.str());
    // l2.push_back(6);
    // s2.clear();
    // s2 << l2;
    // CHECK_NE(s1.str(), s2.str());
}

TEST_CASE("Adding element indeed works.")
{
    CHECK(false);
    // todo repair

    // IntList l;
    // l.push_back(2);
    // CHECK_FALSE(l.empty());
}

TEST_CASE("1a solution.")
{
    CHECK(false);
    // todo repair

    // TrainMap tm;
    // std::string cities[] = {"Sofia", "Pazardzhik", "Plovdiv", "Dimitrovgrad", "StaraZagora", "NovaZagora", "Yambol", "Karnobat", "Burgas"};
    // for (const std::string &s : cities)
    //     tm.push_back(s);
    // tm.addLink("Sofia", "Plovdiv");
    // tm.addLink("Plovdiv", "NovaZagora");
    // tm.addLink("Dimitrovgrad", "NovaZagora");
    // tm.addLink("StaraZagora", "Yambol");
    // tm.addLink("NovaZagora", "Burgas");
    // SUBCASE("Plovdiv->Burgas")
    // {
    //     std::vector<std::string> p = tm.BFSpath("Plovdiv", "StaraZagora");
    //     std::ostringstream s;
    //     for (const std::string &city : p)
    //         s << city << '\n';
    //     CHECK_EQ(s.str(), "Plovdiv\nDimitrovgrad\nStaraZagora\n");
    // }

    // SUBCASE("Sofia->Yambol")
    // {
    //     std::vector<std::string> p = tm.BFSpath("Sofia", "Yambol");
    //     std::ostringstream s;
    //     for (const std::string &city : p)
    //         s << city << '\n';
    //     CHECK_EQ(s.str(), "Sofia\nPlovdiv\nNovaZagora\nYambol\n");
    // }
}

#endif