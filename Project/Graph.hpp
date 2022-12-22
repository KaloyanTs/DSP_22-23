#ifndef __GRAPH_HPP
#define __GRAPH_HPP
#include <map>
#include <string>
#include <utility>
#include <list>

class Graph
{
    using Vertex = std::string;
    using ChildrenList = std::list<std::pair<Vertex, unsigned>>;
    std::map<Vertex, ChildrenList> assArr;

public:
    void addVertex(const std::string &name)
    {
        assArr.insert(std::pair<Vertex, ChildrenList>(name, ChildrenList()));
    }
    void addEdge(const std::string &from, const std::string &to, unsigned w)
    {
        assArr[from].push_back(std::pair<Vertex, unsigned>(to, w));
    }
    bool empty() const { return assArr.empty(); }
};

#endif