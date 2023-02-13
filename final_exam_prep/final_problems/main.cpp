#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node<T> *left, *right;
    Node(const T &d, Node<T> *l, Node<T> *r)
        : data(d), left(l), right(r) {}
};

template <typename T>
void clear(Node<T> *&root)
{
    if (!root)
        return;
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

template <typename T>
void print(Node<T> *root)
{
    if (!root)
    {
        std::cout << "()";
        return;
    }
    std::cout << "( ";
    std::cout << root->data;
    if (root->left || root->right)
    {
        print(root->left);
        std::cout << ' ';
        print(root->right);
    }
    std::cout << " )";
}

Node<char> *rec(Node<char> *root, double result, double c, double &current)
{
    if (root->data >= '0' && root->data <= '9')
    {
        current = root->data - '0';
        if (abs(root->data - '0' - result) <= c)
            return root;
        return nullptr;
    }
    double lRes, rRes;
    Node<char> *l, *r;
    l = rec(root->left, result, c, lRes);
    if (l)
        return l;
    r = rec(root->right, result, c, rRes);
    if (r)
        return r;
    if (root->data == '+')
    {
        if (abs(lRes + rRes - result) <= c)
            return root;
    }
    if (root->data == '-')
    {
        if (abs(lRes - rRes - result) <= c)
            return root;
    }
    if (root->data == '*')
    {
        if (abs(lRes * rRes - result) <= c)
            return root;
    }
    if (root->data == '/')
    {
        if (abs(lRes / rRes - result) <= c)
            return root;
    }
    return nullptr;
}

Node<char> *find(Node<char> *root, double result, double c)
{
    double fict;
    return rec(root, result, c, fict);
}

int main()
{

    return 0;
}