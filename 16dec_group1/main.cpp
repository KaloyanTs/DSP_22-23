#include <iostream>
#include <vector>

struct Node
{
    int data;
    std::vector<Node *> children;
    Node(int _data) : data(_data) {}
};

void insert(Node *root, int x)
{
    root->children.push_back(new Node(x));
}

void clear(Node *&root)
{
    for (Node *&c : root->children)
        clear(c);
    delete root;
    root = nullptr;
}

bool DFS(Node *root, int what, std::vector<int> &path)
{
    if (root->data == what)
        return true;
    else
    {
        for (Node *c : root->children)
        {
            std::vector<int> tmp(path);
            tmp.push_back(c->data);
            if (DFS(c, what, tmp))
            {
                path = tmp;
                return true;
            }
        }
    }
    return false;
}

bool BFS(Node *root, int what, std::vector<int> &path)
{
    if (root->data == what)
        return true;
    else
    {
        for (Node *c : root->children)
            if (c->data == what)
            {
                path.push_back(c->data);
                return true;
            }
        for (Node *c : root->children)
        {
            std::vector<int> tmp(path);
            tmp.push_back(c->data);
            if (BFS(c, what, tmp))
            {
                path = tmp;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    Node *t = new Node(1);
    insert(t, 2);
    insert(t, 3);
    insert(t->children[0], 4);
    insert(t->children[0], 5);
    insert(t->children[0], 6);
    insert(t->children[1], 7);
    insert(t->children[1], 8);

    std::vector<int> p;
    p.push_back(1);
    if (DFS(t, 7, p))
        for (int a : p)
            std::cout << a << ' ';
    else
        std::cout << "No path...";
    std::cout << '\n';

    p = std::vector<int>();
    p.push_back(1);
    if (BFS(t, 7, p))
        for (int a : p)
            std::cout << a << ' ';
    else
        std::cout << "No path...";
    std::cout << '\n';

    clear(t);
    return 0;
}