#include <iostream>
#include <unordered_map>
#include <unordered_set>

class Graph
{
    std::unordered_map<int, std::unordered_set<int>> data;

public:
    void removeEdge(unsigned i, unsigned j)
    {
        data[i].erase(j);
    }
    void addEdge(unsigned i, unsigned j)
    {
        data[i].insert(j);
    }
    bool hasTwoWayPath(unsigned from, unsigned length)
    {
        if (!length)
            return true;
        for (unsigned to : data[from])
            if (data[to].count(from) && hasTwoWayPath(to, length - 1))
                return true;
        return false;
    }
};

int main()
{

    return 0;
}