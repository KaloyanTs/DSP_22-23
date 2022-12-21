#ifndef _SKIP_LIST_HPP
#define _SKIP_LIST_HPP
#include <ostream>

template <typename T>
class SkipList
{
    struct Node
    {
        T data;
        Node *next;
        Node *skip;
        Node(const T &_data, Node *_next = nullptr, Node *_skip = nullptr)
            : data(_data), next(_next), skip(_skip) {}
        void print(std::ostream &os) const;
    };
    Node *begin;
    Node *end;

    Node *find(const T &) const;
    void copy(const SkipList &);
    void clear();

public:
    SkipList();
    SkipList(const T &);
    SkipList(const SkipList &);
    SkipList &operator=(const SkipList &);
    ~SkipList();

    SkipList &push_back(const T &);
    SkipList &addLink(const T &, const T &);
    bool empty() const { return !begin; }
    template <typename C>
    friend std::ostream &operator<<(std::ostream &, const SkipList<C> &);
};

#include "SkipList.ipp"

#endif