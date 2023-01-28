#ifndef __AVL_TREE_HPP
#define __AVL_TREE_HPP

#include <cstddef>
#include <stdexcept>
#include <cassert>
#include <vector>

template <typename T>
struct AVLNode
{
    T data;
    AVLNode *left, *right;
    size_t height;
    AVLNode(const T &d,
            AVLNode *_left = nullptr,
            AVLNode *_right = nullptr)
        : data(d), left(_left), right(_right) {}
    AVLNode *clone() const;
};

template <typename T>
class AVLTree
{
    AVLNode<T> *mRoot;
    void copy(const AVLTree<T> &other);
    void clearEl(AVLNode<T> *&t);
    bool eraseEl(AVLNode<T> *&t, const T &data);
    AVLNode<T> *find(AVLNode<T> *from, const T &el);
    AVLNode<T> *find(AVLNode<T> *from, const T &el) const;
    void insertEl(AVLNode<T> *&from, const T &el);
    void leftToRightEl(const AVLNode<T> *from, std::ostream &os) const;
    void printEl(const AVLNode<T> *from, std::ostream &os = std::cout) const;

    AVLNode<T> *findMinNode(AVLNode<T> *r);
    void updateHeight(AVLNode<T> *node);
    void rotateLeft(AVLNode<T> *&r);
    void rotateRight(AVLNode<T> *&r);
    void balanceRight(AVLNode<T> *&root);
    void balanceLeft(AVLNode<T> *&root);
    size_t height(const AVLNode<T> *node) const;
    size_t balanceFactor(const AVLNode<T> *node) const;
    template <typename FunctionResult>
    void collectEl(AVLNode<T> *from, std::vector<FunctionResult> &res, FunctionResult (*f)(const T &)) const
    {
        if (!from)
            return;
        collectEl(from->left, res, f);
        res.push_back(f(from->data));
        collectEl(from->right, res, f);
    }

public:
    AVLTree() : mRoot(nullptr) {}
    AVLTree(const T &d) : mRoot(new AVLNode<T>(d)) {}
    AVLTree(const AVLTree &);
    AVLTree &operator=(const AVLTree &);
    T root() const;
    size_t height() const { return height(mRoot); }
    bool empty() const { return !mRoot; }
    void clear();
    bool erase(const T &);
    void swap(AVLTree &);
    void print(std::ostream &os = std::cout) const;
    AVLTree &insert(const T &d);
    T *const search(const T &d) const
    {
        AVLNode<T> *const res = find(mRoot, d);
        return (res ? &res->data : nullptr);
    }
    void leftToRight(std::ostream &os = std::cout) { leftToRightEl(mRoot, os); }
    template <typename FunctionResult>
    std::vector<FunctionResult> collect(FunctionResult (*f)(const T &)) const
    {
        std::vector<FunctionResult> res;
        collectEl(mRoot, res, f);
        return res;
    }
    ~AVLTree();
};

template <typename T>
void AVLTree<T>::updateHeight(AVLNode<T> *node)
{
    node->height = 1 + std::max(height(node->left), height(node->right));
}

template <typename T>
void AVLTree<T>::rotateLeft(AVLNode<T> *&r)
{
    assert(r->right);

    AVLNode<T> *originalRight = r->right;
    r->right = originalRight->left;
    originalRight->left = r;
    r = originalRight;
}

template <typename T>
void AVLTree<T>::rotateRight(AVLNode<T> *&r)
{
    assert(r->left);

    AVLNode<T> *originalLeft = r->left;
    r->left = originalLeft->right;
    originalLeft->right = r;
    r = originalLeft;
}

template <typename T>
void AVLTree<T>::balanceRight(AVLNode<T> *&root)
{
    assert(root != nullptr);

    int rootBalance = balanceFactor(root);
    int rightSubTreeBalance = balanceFactor(root->right);
    if (rootBalance == 2)
    {
        if (rightSubTreeBalance == -1)
        {
            rotateRight(root->right);
            updateHeight(root->right->right);
            updateHeight(root->right);
        }
        rotateLeft(root);

        updateHeight(root->left);
    }
    updateHeight(root);
}

template <typename T>
void AVLTree<T>::balanceLeft(AVLNode<T> *&root)
{
    assert(root != nullptr);

    int rootBalance = balanceFactor(root);
    int rightSubTreeBalance = balanceFactor(root->left);
    if (rootBalance == -2)
    {
        if (rightSubTreeBalance == 1)
        {
            rotateLeft(root->left);
            updateHeight(root->left->left);
            updateHeight(root->left);
        }
        rotateRight(root);

        updateHeight(root->right);
        updateHeight(root);
    }
}

template <typename T>
size_t AVLTree<T>::height(const AVLNode<T> *node) const
{
    if (!node)
        return 0;
    return node->height;
}
template <typename T>
size_t AVLTree<T>::balanceFactor(const AVLNode<T> *node) const
{
    if (!node)
        return 0;
    return height(node->right) - height(node->left);
}

template <typename T>
AVLNode<T> *AVLTree<T>::findMinNode(AVLNode<T> *r)
{
    while (r->left)
        r = r->left;
    return r;
}

template <typename T>
AVLNode<T> *AVLTree<T>::find(AVLNode<T> *from, const T &el)
{
    if (!from)
        return nullptr;
    if (from->data == el)
        return from;
    if (from->data > el)
        return find(from->left, el);
    return find(from->right, el);
}

template <typename T>
AVLNode<T> *AVLTree<T>::find(AVLNode<T> *from, const T &el) const
{
    if (!from)
        return nullptr;
    if (from->data == el)
        return from;
    AVLNode<T> *l = find(from->left, el);
    if (l)
        return l;
    return find(from->right, el);
}

template <typename T>
void AVLTree<T>::insertEl(AVLNode<T> *&from, const T &el)
{
    if (!from)
    {
        from = new AVLNode<T>(el);
        from->height = 1;
        return;
    }
    if (from->data < el)
    {
        insertEl(from->right, el);
        updateHeight(from->right);
        balanceRight(from);
    }
    else if (from->data >= el)
    {
        insertEl(from->left, el);
        updateHeight(from->left);
        balanceLeft(from);
    }
}

template <typename T>
AVLTree<T> &AVLTree<T>::insert(const T &d)
{
    insertEl(mRoot, d);
    return *this;
}

template <typename T>
void AVLTree<T>::leftToRightEl(const AVLNode<T> *from, std::ostream &os) const
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
void AVLTree<T>::printEl(const AVLNode<T> *from, std::ostream &os) const
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
void AVLTree<T>::print(std::ostream &os) const
{
    printEl(mRoot, os);
}

template <typename T>
void AVLTree<T>::copy(const AVLTree<T> &other)
{
    if (!other.mRoot)
    {
        mRoot = nullptr;
        return;
    }
    mRoot = other.mRoot->clone();
}

template <typename T>
bool AVLTree<T>::eraseEl(AVLNode<T> *&t, const T &el)
{
    if (!t)
        return false;

    if (t->data < el)
    {
        if (!eraseEl(t->right, el))
            return false;
        updateHeight(t);
        balanceRight(t);
    }
    else if (t->data > el)
    {
        if (!eraseEl(t->left, el))
            return false;
        updateHeight(t);
        balanceLeft(t);
    }
    else if (!t->left && !t->right)
    {
        delete t;
        t = nullptr;
        return true;
    }
    else if (t->left && !t->right)
    {
        AVLNode<T> *toDelete = t;
        t = t->left;
        delete toDelete;
    }
    else if (!t->left && t->right)
    {
        AVLNode<T> *toDelete = t;
        t = t->right;
        delete toDelete;
    }
    else
    {
        t->data = findMinNode(t->right)->data;
        eraseEl(t->right, t->data);
        updateHeight(t);
        balanceRight(t);
    }
    return true;
}

template <typename T>
bool AVLTree<T>::erase(const T &data)
{
    return eraseEl(mRoot, data);
}

template <typename T>
AVLNode<T> *AVLNode<T>::clone() const
{
    AVLNode *lCopy = nullptr;
    if (left)
        lCopy = left->clone();
    AVLNode *rCopy = nullptr;
    if (right)
        rCopy = right->clone();
    return new AVLNode(data, lCopy, rCopy);
}

template <typename T>
void AVLTree<T>::clear()
{
    clearEl(mRoot);
}

template <typename T>
void AVLTree<T>::clearEl(AVLNode<T> *&from)
{
    if (!from)
        return;
    clearEl(from->left);
    clearEl(from->right);
    delete from;
    from = nullptr;
}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T> &other)
    : mRoot(nullptr)
{
    copy(other);
}

template <typename T>
AVLTree<T> &AVLTree<T>::operator=(const AVLTree<T> &other)
{
    if (this == &other)
        return *this;
    clear();
    copy(other);
    return *this;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    clear();
}

template <typename T>
T AVLTree<T>::root() const
{
    if (!mRoot)
        throw std::runtime_error("empty AVLTree");
    return mRoot->data;
}

template <typename T>
void AVLTree<T>::swap(AVLTree &other)
{
    std::swap(mRoot, other.mRoot);
}

#endif