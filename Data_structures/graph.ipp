#ifndef __GRAPH_HPP
#define __GRAPH_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>

template <typename T>
class Graph
{
    using Edge = std::tuple<T, T, int>;
    struct CheaperEdge
    {
        bool operator()(const Edge &a, const Edge &b) { return std::get<2>(a) > std::get<2>(b); }
    };
    using ChildrenList = std::unordered_map<T, int>;
    using AdjList = std::unordered_map<T, ChildrenList>;
    AdjList data;
    unsigned edgeCount;
    bool addEdge(const T &from, const T &to, int weight)
    {
        if (data.count(from) && data[from].count(to))
            return false;
        data[from][to] = weight;
        ++edgeCount;
        return true;
    }
    void recComponent(const T &vertex, std::unordered_set<T> &res) const
    {
        res.insert(vertex);
        if (!data.count(vertex))
            return;
        for (std::pair<T, int> const &edge : data.at(vertex))
            if (!res.count(edge.first))
                recComponent(edge.first, res);
    }
    bool checkCycle(const T &prev, const T &from, std::unordered_set<T> &visited) const
    {
        if (visited.count(from))
            return true;
        if (!data.count(from))
            return false;
        visited.insert(from);
        for (std::pair<T, int> const &edge : data.at(from))
            if (edge.first != prev && checkCycle(from, edge.first, visited))
                return true;
        visited.erase(from);
        return false;
    }

public:
    Graph() : edgeCount(0) {}
    Graph(std::vector<std::tuple<T, T, int>> const &edgesList) : edgeCount(edgesList.size())
    {
        for (std::tuple<T, T, int> const &edge : edgesList)
            data[std::get<0>(edge)][std::get<1>(edge)] = std::get<2>(edge);
    }
    bool removeEdge(const T &from, const T &to)
    {
        if (!data.count(from) || !data.at(from).count(to))
            return false;
        data[from].erase(to);
        --edgeCount;
        return true;
    }
    bool hasCycle() const
    {
        std::unordered_set<T> visited;
        return checkCycle(T(), data.cbegin()->first, visited);
    }
    std::vector<T> neighbours(const T &vertex) const
    {
        std::vector<T> res;
        for (std::pair<T, int> &edge : data[vertex])
            res.push_back(edge.first);
        return res;
    }
    unsigned degree(const T &vertex) const
    {
        if (!data.count(vertex))
            return data[vertex].size();
        throw std::exception("Vertex not found");
    }
    bool isEdge(const T &from, const T &to)
    {
        return data.count(from) && data[from].count(to);
    }
    int edgeWeight(const T &from, const T &to)
    {
        if (isEdge(from, to))
            return data[from][to];
        throw std::exception();
        return 0;
    }
    friend std::ostream &operator<<(std::ostream &os, const Graph<T> &g)
    {
        os << g.edgeCount << '\n';
        for (const std::pair<T, std::unordered_map<T, int>> &row : g.data)
            for (const std::pair<T, int> &edge : row.second)
                os << row.first << ' ' << edge.first << ' ' << edge.second << '\n';
        return os;
    }
    friend std::istream &operator>>(std::istream &is, Graph<T> &g)
    {
        unsigned count;
        is >> count;
        g.edgeCount = 0;
        g.data.clear();
        T from, to;
        int w;
        for (unsigned i = 0; i < count; ++i)
        {
            is >> from >> to >> w;
            g.addEdge(from, to, w);
        }
        return is;
    }
    std::unordered_set<T> vertices() const
    {
        std::unordered_set<T> vertices;
        for (std::pair<T, std::unordered_map<T, int>> const &p : data)
        {
            vertices.insert(p.first);
            for (std::pair<T, int> const &edge : p.second)
                vertices.insert(edge.first);
        }
        return vertices;
    }
    std::unordered_set<T> component(const T &vertex) const
    {
        if (!data.count(vertex))
            throw std::exception();
        std::unordered_set<T> res;
        recComponent(vertex, res);
        return res;
    }
    Graph<T> MSTPrim() const
    {
        Graph<T> res;
        int minCost = (*(*data.begin()).second.begin()).second;
        T minCostTo = (*(*data.begin()).second.begin()).first;
        for (std::pair<T, int> const &edge : (*data.begin()).second)
        {
            if (edge.second < minCost)
            {
                minCost = edge.second;
                minCostTo = edge.first;
            }
        }
        res.addEdge((*data.begin()).first, minCostTo, minCost);

        return res;
        // todo implement
    }
    std::vector<T> BFS(const T &from)
    {
        std::queue<T> q;
        std::unordered_set<T> visited;
        std::vector<T> res;
        q.push(from);
        T current;
        while (!q.empty())
        {
            current = q.front();
            q.pop();
            visited.insert(current);
            res.push_back(current);
            for (std::pair<T, int> edge : data[current])
                if (!visited.count(edge.first))
                    q.push(edge.first);
        }
        return res;
    }

    std::vector<T> DFS(const T &from)
    {
        std::stack<T> q;
        std::unordered_set<T> visited;
        std::vector<T> res;
        q.push(from);
        T current;
        while (!q.empty())
        {
            current = q.top();
            q.pop();
            visited.insert(current);
            res.push_back(current);
            for (std::pair<T, int> edge : data[current])
                if (!visited.count(edge.first))
                    q.push(edge.first);
        }
        return res;
    }
    std::vector<Edge> edges() const
    {
        std::vector<Edge> res;
        for (std::pair<T, std::unordered_map<T, int>> const &p : data)
            for (std::pair<T, int> const &edge : p.second)
                res.push_back(Edge(p.first, edge.first, edge.second));
        return res;
    }
    Graph<T> KruskalMST() const
    {
        Graph<T> res;
        if (component(data.cbegin()->first).size() < data.size())
            return res;
        std::priority_queue<Edge, std::vector<Edge>, CheaperEdge> q;
        Edge edge;
        for (std::pair<T, std::unordered_map<T, int>> const &p : data)
            for (std::pair<T, int> const &edge : p.second)
            {
                q.push(std::tuple<T, T, int>(p.first, edge.first, edge.second));
                q.push(std::tuple<T, T, int>(edge.first, p.first, edge.second));
            }
        size_t i = 0;
        size_t neededEdges = vertices().size() - 1;
        while (i < neededEdges)
        {
            edge = q.top();
            q.pop();
            if (res.isEdge(std::get<0>(edge), std::get<1>(edge)))
                continue;
            res.addEdge(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge));
            res.addEdge(std::get<1>(edge), std::get<0>(edge), std::get<2>(edge));
            if (res.hasCycle())
            {
                res.removeEdge(std::get<0>(edge), std::get<1>(edge));
                res.removeEdge(std::get<1>(edge), std::get<0>(edge));
            }
            else
                ++i;
        }
        return res;
    }
};

#endif