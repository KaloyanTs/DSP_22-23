#ifndef __GRAPH_TESTS_HPP
#define __GRAPH_TESTS_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "doctest.h"
#include "graph.ipp"

void readGraph(const std::string &path, Graph<std::string> &g)
{
    std::ifstream ifs;
    ifs.open(path);
    REQUIRE(ifs.is_open());
    ifs >> g;
    ifs.close();
}

TEST_CASE("Reading a graph")
{
    Graph<std::string> g;
    readGraph("../graphs_examples/g1.graph", g);
    CHECK(g.isEdge("A", "B"));
    CHECK(g.isEdge("B", "C"));
    CHECK(g.isEdge("C", "A"));
    CHECK_EQ(g.edgeWeight("A", "B"), 4);
    CHECK_EQ(g.edgeWeight("B", "C"), 1);
    CHECK_EQ(g.edgeWeight("C", "A"), 6);
}

TEST_CASE("Connected components")
{
    Graph<std::string> g;
    readGraph("../graphs_examples/g2.graph", g);
    std::unordered_set<std::string> c = g.component("A");
    CHECK(c.count("A"));
    CHECK(c.count("B"));
    CHECK(c.count("C"));
    CHECK_FALSE(c.count("D"));
    CHECK_FALSE(c.count("E"));
    CHECK_FALSE(c.count("F"));
}

TEST_CASE("BFS")
{
    Graph<std::string> g;
    readGraph("../graphs_examples/g2.graph", g);
    std::vector<std::string> c = g.BFS("A");
    typename std::vector<std::string>::const_iterator i = c.cbegin();
    REQUIRE_EQ(c.size(), 3);
    CHECK_EQ(*i++, "A");
    CHECK_EQ(*i++, "B");
    CHECK_EQ(*i++, "C");
    CHECK_EQ(i, c.cend());
}

TEST_CASE("DFS")
{
    Graph<std::string> g;
    readGraph("../graphs_examples/g2.graph", g);
    std::vector<std::string> c = g.DFS("A");
    typename std::vector<std::string>::const_iterator i = c.cbegin();
    REQUIRE_EQ(c.size(), 3);
    CHECK_EQ(*(i++), "A");
    CHECK_EQ(*(i++), "B");
    CHECK_EQ(*(i++), "C");
    CHECK_EQ(i, c.cend());
}

TEST_CASE("Проверка за цикли")
{
    Graph<std::string> g;
    readGraph("../graphs_examples/g1.graph", g);
    CHECK(g.hasCycle());
    readGraph("../graphs_examples/g2.graph", g);
    CHECK_FALSE(g.hasCycle());
}

TEST_CASE("Kruskal MST generation")
{
    Graph<std::string> g;
    readGraph("../graphs_examples/g3.graph", g);
    g = g.KruskalMST();
    std::unordered_set<std::string> vertices = g.vertices();
    std::vector<std::tuple<std::string, std::string, int>> edges = g.edges();
    for (const std::string &v : {"0", "1", "2", "3", "4", "5"})
        CHECK(vertices.count(v));
    int sum = 0;
    for (std::tuple<std::string, std::string, int> const &edge : edges)
        sum += std::get<2>(edge);
    sum >>= 1;  // every edge counted twice from each direction
    CHECK_EQ(sum, 16);
}

#endif