#include "Graph.hpp"
#include <set>

unsigned Graph::uniquesCount(const std::list<std::string> &x)
{
    std::set<Vertex> res;
    for (const Vertex &v : x)
        res.insert(v);
    return res.size();
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
std::list<Vertex> Graph::mostCitiesGivenTotalPrice(const std::string &begin, const std::string &end, unsigned limit)
{
    const ChildrenList &beginPaths = assArr[begin];
    std::list<Vertex> res;
    res.push_back(begin);
    std::list<Vertex> tmp, maxL;
    unsigned maxDiff = 0, currDiff = 0;
    for (const WeightedPathTo &p : beginPaths)
    {
        if (p.second <= limit)
        {
            tmp = mostCitiesGivenTotalPrice(p.first, end, limit - p.second);
            currDiff = uniquesCount(tmp);
            // todo try using no recursion but a stack
            if (tmp.back() == end && currDiff > maxDiff)
            {
                maxL = std::move(tmp);
                maxDiff = currDiff;
            }
        }
    }
    // todo use another stl structure allowing to std::move the maxL and then push_front the begin
    res.insert(res.end(), maxL.begin(), maxL.end());
    return res;
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