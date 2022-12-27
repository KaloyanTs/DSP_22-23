#include "Graph.hpp"
#include <set>
#include <stack>
#include <tuple>

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

#include <iostream> //todo remove

std::list<Vertex> Graph::mostVerticesGivenTotalPrice2(const std::string &begin, const std::string &end, unsigned limit)
{
    using V = std ::string;
    using Frame = std::tuple<V, unsigned, std::list<V>>;
    std::stack<Frame> st;
    std::list<V> maxPath;
    size_t maxVisited = 1;
    maxPath.push_back(begin);
    Frame current = std::make_tuple(begin, limit, maxPath);
    st.push(current);
    while (!st.empty())
    {
        current = std::move(st.top());
        std::clog << "From: " << std::get<0>(current) << '\n'; // todo remove
        std::clog << "\tCurrentPath: ";                        // todo remove
        for (const std::string &c : std::get<2>(current))      // todo remove
            std::clog << c << '\t';                            // todo remove
        std::clog << '\n';                                     // todo remove
        st.pop();
        if (std::get<0>(current) == end)
        {
            size_t currentVisited = Graph::uniquesCount(std::get<2>(current));
            if (currentVisited > maxVisited)
            {
                maxPath = std::move(std::get<2>(current));
                maxVisited = currentVisited;
            }
        }
        const ChildrenList *beginPaths = &assArr[std::get<0>(current)];
        for (const WeightedPathTo &p : *beginPaths)
        {
            if (p.second <= limit)
            {
                std::get<2>(current).push_back(p.first);
                st.push(std::make_tuple(p.first,
                                        limit - p.second,
                                        std::move(std::get<2>(current))));
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