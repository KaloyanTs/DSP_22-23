#include "Graph.hpp"
#include <set>
#include <stack>
#include <tuple>

#define frameFrom std::get<0>
#define frameLimit std::get<1>
#define framePath std::get<2>

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
    if (assArr.find(from) == assArr.end())
        addVertex(from);
    if (assArr.find(to) == assArr.end())
        addVertex(to);
    assArr[from].push_back(std::pair<Vertex, unsigned>(to, w));
    assArr[to].push_back(std::pair<Vertex, unsigned>(from, w));
    return *this;
}
std::list<Vertex> Graph::mostVerticesGivenTotalPrice(const std::string &begin, const std::string &end, unsigned limit)
{
    using Frame = std::tuple<
        std ::string,            // from which vertex
        unsigned,                // currentLimit
        std::list<std::string>>; // currentPath
    std::stack<Frame> st;
    std::list<std ::string> maxPath;
    size_t maxVisited = 1, currentVisited;
    const ChildrenList *beginPaths{nullptr};
    maxPath.push_back(begin);
    Frame current = std::make_tuple(begin, limit, maxPath);
    st.push(current);
    while (!st.empty())
    {
        current = std::move(st.top());
        st.pop();
        if (frameFrom(current) == end)
        {
            currentVisited = Graph::uniquesCount(framePath(current));
            if (currentVisited > maxVisited)
            {
                maxPath = std::move(framePath(current));
                maxVisited = currentVisited;
            }
        }
        beginPaths = &assArr[frameFrom(current)];
        for (const WeightedPathTo &p : *beginPaths)
        {
            if (p.second <= frameLimit(current))
            {
                framePath(current).push_back(p.first);
                st.push(std::make_tuple(p.first,
                                        frameLimit(current) - p.second,
                                        framePath(current)));
                framePath(current).pop_back();
            }
        }
    }
    return maxPath;
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