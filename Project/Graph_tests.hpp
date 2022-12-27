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

TEST_CASE("Printing Graph data")
{

    Graph g;
    g.addVertex("A").addVertex("B").addVertex("C").addVertex("D").addVertex("E").addVertex("F");

    g.addEdge("A", "B", 18).addEdge("A", "C", 2).addEdge("A", "D", 5).addEdge("B", "D", 14).addEdge("B", "E", 12).addEdge("D", "E", 7).addEdge("C", "F", 20).addEdge("D", "F", 26);

    std::ostringstream s;
    s << g;
    CHECK_EQ(s.str(), "A\t->\tB(18)\tC(2)\tD(5)\nB\t->\tA(18)\tD(14)\tE(12)\nC\t->\tA(2)\tF(20)\nD\t->\tA(5)\tB(14)\tE(7)\tF(26)\nE\t->\tB(12)\tD(7)\nF\t->\tC(20)\tD(26)\n");
}

TEST_CASE("Walk through cities")
{
    Graph g;
    std::string sites[] = {"DzhumayaSquare", "HistoricalMuseum", "RomanStadium", "ArtGallery", "AntiqueTheatre", "Railstation"};
    g.addVertex(sites[0]).addVertex(sites[1]).addVertex(sites[2]).addVertex(sites[3]).addVertex(sites[4]).addVertex(sites[5]);

    g.addEdge(sites[0], sites[1], 18).addEdge(sites[0], sites[2], 2).addEdge(sites[0], sites[3], 5).addEdge(sites[1], sites[3], 14).addEdge(sites[1], sites[4], 12).addEdge(sites[3], sites[4], 7).addEdge(sites[2], sites[5], 20).addEdge(sites[3], sites[5], 26);

    std::list<std::string> res = g.mostVerticesGivenTotalPrice("Railstation", "Railstation", 68);

    // for (const std::string &city : res)
    //     std::clog << city << '\t';
    // std::clog << '\n';
    // todo test for the names and order of the cities

    CHECK_EQ(Graph::uniquesCount(res), 5);
}

#endif