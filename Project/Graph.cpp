#include "Graph.hpp"
#include <set>

unsigned Graph::uniquesCount(const std::list<std::string> &x)
{
    std::set<Vertex> res;
    for (const Vertex &v : x)
        res.insert(v);
    return res.size();
}

Graph Graph::readFromFile(const std::string &)
{
    // todo check whether move semantics should be written for Graph
    // todo implement correctly
    return Graph();
}

Graph &Graph::addVertex(const std::string &name)
{
    assArr.insert(std::pair<Vertex, ChildrenList>(name, ChildrenList()));
    return *this;
}
Graph &Graph::addEdge(const std::string &from, const std::string &to, unsigned w)
{
    assArr[from].push_back(std::pair<Vertex, unsigned>(to, w));
    assArr[to].push_back(std::pair<Vertex, unsigned>(from, w));
    return *this;
}
std::list<Vertex> Graph::mostVerticesGivenTotalPrice(const std::string &begin, const std::string &end, unsigned limit)
{
    const ChildrenList &beginPaths = assArr[begin];
    std::list<Vertex> tmp, maxL;
    unsigned maxDiff = 0, currDiff = 0;
    for (const WeightedPathTo &p : beginPaths)
    {
        if (p.second <= limit)
        {
            tmp = mostVerticesGivenTotalPrice(p.first, end, limit - p.second);
            currDiff = uniquesCount(tmp);
            // todo try using no recursion but a stack
            if (tmp.back() == end && currDiff > maxDiff)
            {
                maxL = std::move(tmp);
                maxDiff = currDiff;
            }
        }
    }
    maxL.push_front(begin);
    return maxL;
}

std::ostream &operator<<(std::ostream &os, const Graph &g)
{
    for (const std::pair<Vertex, ChildrenList> &p : g.assArr)
    {
        os << p.first << "\t->\t";
        for (const WeightedPathTo &v : p.second)
        {
            if (&v != &(*p.second.begin()))
                os << '\t';
            os << v.first << '(' << v.second << ')';
        }
        os << '\n';
    }
    return os;
}