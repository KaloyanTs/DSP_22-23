#include <iostream>
#include <map>
#include <forward_list>
#include <set>
#include <vector>

// using GraphAdjList = std::map<std::string, std::forward_list<std::string>>;
using GraphAdjList = std::vector<std::vector<int>>;

void visit(const GraphAdjList &g, int from, std::set<int> &visited)
{
    if (visited.find(from) != visited.end())
        return;
    visited.insert(from);
    for (int to : g[from])
    {
        if (visited.find(to) == visited.end())
        {
            visit(g, to, visited);
        }
    }
}

int countComponents(const GraphAdjList &g)
{
    size_t count = 0;

    std::set<int> visited;

    for (unsigned i = 0; i < g.size(); ++i)
        if (visited.find(i) == visited.end())
        {
            visit(g, i, visited);
            ++count;
        }
    return count;
}

bool traverse(const GraphAdjList &g, int prev, int from, std::set<int> &visited)
{
    if (visited.find(from) != visited.end() && prev != -1)
        return true;
    visited.insert(from);
    for (int to : g[from])
    {
        if (to != prev && traverse(g, from, to, visited))
            return true;
    }
    return false;
}

bool isCyclic(const GraphAdjList &g)
{
    std::set<int> visited;
    unsigned i = 0;
    while (i < g.size() && !(visited.find(i) == visited.end() && traverse(g, -1, i, visited)))
        ++i;
    return i < g.size();
}

void addEdge(GraphAdjList &g, int from, int to)
{
    g[from].push_back(to);
    g[to].push_back(from);
}

int main()
{
    GraphAdjList g(8);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 3, 4);
    addEdge(g, 3, 6);
    addEdge(g, 4, 6);
    addEdge(g, 5, 7);

    std::cout << countComponents(g) << '\n';
    std::cout << isCyclic(g) << '\n';

    return 0;
}