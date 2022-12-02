#include <iostream>
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

using intTree = Node<int>;

int main()
{
    intTree *root = new intTree{1,
                                {new intTree{2},
                                 new intTree{3},
                                 new intTree{4}}};

    std::cout << "height: " << height(root) << '\n';
    std::cout << "leaves: " << countLeaves(root) << '\n';
    std::cout << "has root equal to sum of children: "
              << std::boolalpha << hasRootEqSumOfChildren(root) << '\n';
    printHeightN(2, root);
    std::cout << '\n';

    clear(root);
    return 0;
}