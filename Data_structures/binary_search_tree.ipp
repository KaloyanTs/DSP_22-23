#ifndef __BINARY_SEARCH_TREE_HPP
#define __BINARY_SEARCH_TREE_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
struct BinarySearchTreeEl
{
    T data;
    BinarySearchTreeEl *left, *right;
    BinarySearchTreeEl(const T &d,
                       BinarySearchTreeEl *_left = nullptr,
                       BinarySearchTreeEl *_right = nullptr)
        : data(d), left(_left), right(_right) {}
    BinarySearchTreeEl *clone() const;
};

template <typename T>
class BinarySearchTree
{
    BinarySearchTreeEl<T> *mRoot;
    void copy(const BinarySearchTree<T> &other);
    void clearEl(BinarySearchTreeEl<T> *&t);
    size_t depthEl(const BinarySearchTreeEl<T> *r) const;
    BinarySearchTreeEl<T> *find(BinarySearchTreeEl<T> *from, const T &el);
    void insertEl(BinarySearchTreeEl<T> *&from, const T &el);
    void leftToRightEl(const BinarySearchTreeEl<T> *from, std::ostream &os) const;
    void printEl(const BinarySearchTreeEl<T> *from, std::ostream &os = std::cout) const;

public:
    BinarySearchTree() : mRoot(nullptr) {}
    BinarySearchTree(const T &d) : mRoot(new BinarySearchTreeEl<T>(d)) {}
    BinarySearchTree(const BinarySearchTree &);
    BinarySearchTree &operator=(const BinarySearchTree &);
    T root() const;
    bool empty() const { return !mRoot; }
    void clear();
    void swap(BinarySearchTree &);
    void print(std::ostream &os = std::cout) const;
    BinarySearchTree &insert(const T &d);
    bool search(const T &d) { return find(mRoot, d); }
    void leftToRight(std::ostream &os = std::cout) { leftToRightEl(mRoot, os); }
    const size_t depth() { return depthEl(mRoot); }
    ~BinarySearchTree();
};

template <typename T>
BinarySearchTreeEl<T> *BinarySearchTree<T>::find(BinarySearchTreeEl<T> *from, const T &el)
{
    if (!from)
        return nullptr;
    if (from->data == el)
        return from;
    BinarySearchTreeEl<T> *l = find(from->left, el);
    if (l)
        return l;
    return find(from->right, el);
}

template <typename T>
void BinarySearchTree<T>::insertEl(BinarySearchTreeEl<T> *&from, const T &el)
{
    if (!from)
    {
        from = new BinarySearchTreeEl<T>(el);
        return;
    }
    if (el <= from->data)
        insertEl(from->left, el);
    else
        insertEl(from->right, el);
}

template <typename T>
BinarySearchTree<T> &BinarySearchTree<T>::insert(const T &d)
{
    insertEl(mRoot, d);
    return *this;
}

template <typename T>
void BinarySearchTree<T>::leftToRightEl(const BinarySearchTreeEl<T> *from, std::ostream &os) const
{
    if (from->left)
    {
        leftToRightEl(from->left, os);
        os << ' ';
    }
    os << from->data;
    if (from->right)
    {
        os << ' ';
        leftToRightEl(from->right, os);
    }
}

template <typename T>
size_t BinarySearchTree<T>::depthEl(const BinarySearchTreeEl<T> *r) const
{
    if (!r)
        return 0;
    return 1 + std::max(depthEl(mRoot->left), depthEl(mRoot->right));
}

template <typename T>
void BinarySearchTree<T>::printEl(const BinarySearchTreeEl<T> *from, std::ostream &os) const
{
    if (!from)
    {
        os << "()";
        return;
    }
    os << '(' << from->data;
    if (from->left || from->right)
    {
        os << ' ';
        printEl(from->left, os);
        os << ' ';
        printEl(from->right, os);
    }
    os << ')';
}

template <typename T>
void BinarySearchTree<T>::print(std::ostream &os) const
{
    printEl(mRoot, os);
}

template <typename T>
void BinarySearchTree<T>::copy(const BinarySearchTree<T> &other)
{
    if (!other.mRoot)
    {
        mRoot = nullptr;
        return;
    }
    mRoot = other.mRoot->clone();
}

template <typename T>
void BinarySearchTree<T>::clearEl(BinarySearchTreeEl<T> *&t)
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
BinarySearchTreeEl<T> *BinarySearchTreeEl<T>::clone() const
{
    BinarySearchTreeEl *lCopy = nullptr;
    if (left)
        lCopy = left->clone();
    BinarySearchTreeEl *rCopy = nullptr;
    if (right)
        rCopy = right->clone();
    return new BinarySearchTreeEl(data, lCopy, rCopy);
}

template <typename T>
void BinarySearchTree<T>::clear()
{
    clearEl(mRoot);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &other)
    : mRoot(nullptr)
{
    copy(other);
}

template <typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(const BinarySearchTree<T> &other)
{
    if (this == &other)
        return *this;
    clear();
    copy(other);
    return *this;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    clear();
}

template <typename T>
T BinarySearchTree<T>::root() const
{
    if (!mRoot)
        throw std::runtime_error("empty BinarySearchTree");
    return mRoot->data;
}

template <typename T>
void BinarySearchTree<T>::swap(BinarySearchTree &other)
{
    std::swap(mRoot, other.mRoot);
}

#endif