#ifndef __GRAPH_HPP
#define __GRAPH_HPP
#include <ostream>
#include <map>
#include <string>
#include <utility>
#include <list>

using Vertex = std::string;
using WeightedPathTo = std::pair<Vertex, unsigned>;
using ChildrenList = std::list<WeightedPathTo>;

class Graph
{
    std::map<Vertex, ChildrenList> assArr;

public:
    static unsigned uniquesCount(const std::list<Vertex> &);

    Graph &addVertex(const std::string &);
    Graph &addEdge(const std::string &, const std::string &, unsigned);
    std::list<Vertex> mostCitiesGivenTotalPrice(const std::string &, const std::string &, unsigned);
    friend std::ostream &operator<<(std::ostream &, const Graph &);
    bool empty() const { return assArr.empty(); }
};

#endif