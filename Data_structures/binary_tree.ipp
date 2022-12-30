#ifndef __BINARY_TREE_HPP
#define __BINARY_TREE_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
struct BinaryTreeEl
{
    T data;
    BinaryTreeEl *left, *right;
    BinaryTreeEl(const T &d,
                 BinaryTreeEl *_left = nullptr,
                 BinaryTreeEl *_right = nullptr)
        : data(d), left(_left), right(_right) {}
    BinaryTreeEl *clone() const;
};

template <typename T>
struct BinaryTree
{
    BinaryTreeEl<T> *mRoot;
    void copy(const BinaryTree<T> &other);
    void clearEl(const BinaryTreeEl<T> *&t);
    size_t depthEl(const BinaryTreeEl<T> *r) const;

public:
    BinaryTree() : mRoot(nullptr) {}
    BinaryTree(const T &d) : mRoot(new BinaryTreeEl(d)) {}
    BinaryTree(const BinaryTree &);
    BinaryTree(T const &mRoot, BinaryTree &&left = BinaryTree(), BinaryTree &&right = BinaryTree());
    BinaryTree &operator=(const BinaryTree &);
    T root() const;
    bool empty() const { return !root; }
    void clear();
    void swap(BinaryTree &other);
    void print(std::ostream &os = std::cout) const;
    size_t depth() { return depthEl(root); }
    ~BinaryTree();
};

template <typename T>
size_t BinaryTree<T>::depthEl(const BinaryTreeEl<T> *r) const
{
    if (!r)
        return 0;
    return 1 + std::max(depthEl(root->left), depthEl(root->right));
}

template <typename T>
void BinaryTree<T>::print(std::ostream &os = std::cout) const
{
    if (!root)
    {
        os << "()";
        return;
    }
    os << '(' << root->data;
    if (left || right)
    {
        os << ' ';
        print(root->left);
        os << ' ';
        print(root->right);
    }
    os << ')';
}

template <typename T>
void BinaryTree<T>::copy(const BinaryTree<T> &other)
{
    if (!other.mRoot)
    {
        mRoot = nullptr;
        return;
    }
    mRoot = other.mRoot->clone();
}

template <typename T>
void BinaryTree<T>::clearEl(const BinaryTreeEl<T> *&t)
{
    if (!t)
        return;
    if (t->left)
        clearEl(t->left);
    if (t->right)
        clearEl(t->right);
    delete t;
    t = nullptr;
}

template <typename T>
BinaryTreeEl<T> *BinaryTreeEl<T>::clone() const
{
    BinaryTreeEl *lCopy = nullptr;
    if (left)
        lCopy = left->clone();
    BinaryTreeEl *rCopy = nullptr;
    if (right)
        rCopy = right->clone();
    return new BinaryTreeEl(data, lCopy, rCopy);
}

template <typename T>
void BinaryTree<T>::clear()
{
    clearEl(mRoot);
}

template <typename T>
BinaryTree<T>::BinaryTree(T const &mRoot, BinaryTree &&left = BinaryTree(), BinaryTree &&right = BinaryTree())
{
    mRoot = new BinaryTreeEl<T>(mRoot, left.mRoot, right.mRoot);
    left.mRoot = right.mRoot = nullptr;
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &other)
    : head(nullptr), tail(nullptr)
{
    copy(other);
}

template <typename T>
BinaryTree<T> &BinaryTree<T>::operator=(const BinaryTree<T> &other)
{
    if (this == &other)
        return *this;
    clear();
    copy(other);
    return *this;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    clear();
}

template <typename T>
T BinaryTree<T>::root() const
{
    if (!mRoot)
        throw std::runtime_error("empty BinaryTree");
    return mRoot->data;
}

template <typename T>
void BinaryTree<T>::swap(BinaryTree &other)
{
    std::swap(mRoot, other.mRoot);
}

#endif