#include <iostream>
#include <map>
#include <forward_list>
#include <set>
#include <vector>

using GraphAdjList = std::map<const std::string, std::forward_list<std::string>>;

void visit(GraphAdjList &g, const std::string &from, std::set<std::string> &visited)
{
    if (visited.find(from) != visited.end())
        return;
    visited.insert(from);
    for (const std::string &to : g[from])
    {
        if (visited.find(to) == visited.end())
        {
            visit(g, to, visited);
        }
    }
}

int countComponents(GraphAdjList &g)
{
    size_t count = 0;

    std::set<std::string> visited;

    for (const std::pair< std::string, std::forward_list< std::string>> &i : g)
        if (visited.find(i.first) == visited.end())
        {
            visit(g, i.first, visited);
            ++count;
        }
    return count;
}

bool traverse(GraphAdjList &g, const std::string &prev, const std::string &from, std::set<std::string> &visited)
{
    if (visited.find(from) != visited.end() && prev != "")
        return true;
    visited.insert(from);
    for (const std::string &to : g[from])
    {
        if (to != prev && traverse(g, from, to, visited))
            return true;
    }
    return false;
}

bool isCyclic(GraphAdjList &g)
{
    std::set<std::string> visited;

    for (const std::pair< std::string, std::forward_list< std::string>> &from : g)
    {
        if (visited.find(from.first) == visited.end() && traverse(g, "", from.first, visited))
            return true;
    }
    return false;
}

void addEdge(GraphAdjList &g, const std::string &from, const std::string &to)
{
    g[from].push_front(to);
    g[to].push_front(from);
}

int main()
{
    GraphAdjList g;
    addEdge(g, "A", "B");
    addEdge(g, "A", "C");
    addEdge(g, "B", "D");
    addEdge(g, "C", "D");
    addEdge(g, "D", "E");
    addEdge(g, "D", "F");

    std::cout << countComponents(g) << '\n';
    std::cout << isCyclic(g) << '\n';

    return 0;
}