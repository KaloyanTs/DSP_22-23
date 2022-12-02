#include <iostream>
#include <string>
#include <list>

template <typename T>
struct Node
{
    T data;
    std::list<Node *> children;
};

template <typename T>
void clear(Node<T> *&root)
{
    if (!root)
        return;
    for (Node<T> *child : root->children)
        clear(child);
    delete root;
    root = nullptr;
}

template <typename T>
size_t height(const Node<T> *root)
{
    if (!root)
        return 0;
    size_t maxH = 0;
    size_t tmp;
    for (const Node<T> *r : root->children)
    {
        tmp = height(r);
        if (tmp > maxH)
            maxH = tmp;
    }
    return maxH + 1;
}

template <typename T>
size_t countLeaves(const Node<T> *root)
{
    if (!root)
        return 0;
    if (root->children.empty())
        return 1;
    size_t res = 0;
    for (const Node<T> *r : root->children)
        res += countLeaves(r);
    return res;
}

template <typename T>
void printHeightN(size_t h, const Node<T> *root)
{
    if (!root)
        return;
    if (h == 1)
        std::cout << root->data << ' ';
    for (const Node<T> *r : root->children)
        printHeightN(h - 1, r);
}

template <typename T>
bool hasRootEqSumOfChildren(const Node<T> *root)
{
    if (!root || root->children.empty())
        return false;
    size_t sum = 0;
    for (const Node<T> *r : root->children)
        sum += r->data;
    if (sum == root->data)
        return true;
    for (const Node<T> *r : root->children)
        if (hasRootEqSumOfChildren(r))
            return true;
    return false;
}

template <typename T>
bool pathToLeafWithSum(const Node<T> *root, int sum)
{
    if (!root)
        return false;
    if (root->children.empty())
        return sum == root->data;
    for (const Node<T> *r : root->children)
        if (pathToLeafWithSum(r, sum - root->data))
            return true;
    return false;
}

using Folder = Node<std::string>;

std::string pathTo(const Folder *root, const std::string &to)
{
    if (!root)
        return "";
    if (root->children.empty() && root->data == to)
        return to;
    if (root->children.empty())
        return "";
    std::string tmp;
    for (const Folder *f : root->children)
    {
        tmp = pathTo(f, to);
        if (tmp != "")
            return root->data + "/" + tmp;
    }
    return "";
}

std::string findRelativePath(const Folder *root,
                             const std::string &from,
                             const std::string &to)
{
    if (!root)
        return "";
    std::string res;
    for (const Folder *f : root->children)
        if (f->data == from)
        {
            for (const Folder *ff : f->children)
            {
                res = pathTo(ff, to);
                if (res != "")
                    return "./" + res;
            }
        }
    return "";
}

using intTree = Node<int>;

int main()
{
    intTree *root = new intTree{9,
                                {new intTree{2},
                                 new intTree{3},
                                 new intTree{4}}};

    std::cout << "height: " << height(root) << '\n';
    std::cout << "leaves: " << countLeaves(root) << '\n';
    std::cout << "has root equal to sum of children: "
              << std::boolalpha << hasRootEqSumOfChildren(root) << '\n';
    printHeightN(2, root);
    std::cout << '\n';
    std::cout << "path to leaf with sum 4: "
              << std::boolalpha
              << pathToLeafWithSum(root, 4) << '\n';
    std::cout << "has root equal to sum of children: "
              << std::boolalpha << hasRootEqSumOfChildren(root) << '\n';
    std::cout << '\n';

    clear(root);

    Folder *f = new Folder{"",
                           {new Folder{"bin", {
                                                  new Folder{"cp"},
                                                  new Folder{"ksh"},
                                                  new Folder{"is"},
                                                  new Folder{"pwd"},
                                              }},
                            new Folder{"dev"}, new Folder{"etc", {new Folder{"passwd"}}}, new Folder{"home", {new Folder{"mthomas", {new Folder{"bin"}, new Folder{"class_stuff", {new Folder{"foo"}, new Folder{"bar"}}}, new Folder{"profile"}}}}}, new Folder{"lib"}, new Folder{"mnt"}, new Folder{"proc"}, new Folder{"root"}, new Folder{"sbin"}, new Folder{"tmp"}, new Folder{"usr", {new Folder{"bin"}}}}};

    std::cout << findRelativePath(f, "home", "bar") << '\n';
    clear(f);
    return 0;
}