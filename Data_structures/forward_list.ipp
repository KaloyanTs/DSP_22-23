#ifndef __FORWARD_LIST_HPP
#define __FORWARD_LIST_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
struct ForwardListEl
{
    T data;
    ForwardListEl *next;
    ForwardListEl(const T &d, ForwardListEl *_next = nullptr) : data(d), next(_next) {}
};

template <typename T>
class ForwardList
{
public:
    class Iterator
    {
        ForwardListEl<T> *ptr;

    public:
        Iterator(ForwardListEl<T> *_ptr = nullptr) : ptr(_ptr) {}
        T &operator*() { return ptr->data; }
        Iterator &operator++();
        Iterator operator++(int);
        bool operator==(const Iterator &other) { return ptr == other.ptr; }
        bool operator!=(const Iterator &other) { return ptr != other.ptr; }
        operator bool() { return ptr; }
        friend class ForwardList<T>;
    };

private:
    ForwardListEl<T> *head, *tail;
    size_t mSize;
    void copy(const ForwardList<T> &other);

public:
    ForwardList() : head(nullptr), tail(nullptr), mSize(0) {}
    ForwardList(const T &d) : head(new ForwardListEl<T>(d)), tail(head), mSize(1) {}
    ForwardList(const ForwardList &);
    ForwardList &operator=(const ForwardList &);
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
    void push_front(const T &data);
    void push_back(const T &data);
    void pop_front();
    T front() const;
    T back() const;
    bool empty() const { return !head; }
    size_t size() const { return mSize; }
    void insertAfter(const Iterator &pos, const T &el);
    void eraseAfter(Iterator &pos);
    void clear();
    void swap(ForwardList &other);
    ~ForwardList();
};

template <typename T>
ForwardList<T>::ForwardList(const ForwardList<T> &other)
    : head(nullptr), tail(nullptr)
{
    copy(other);
}

template <typename T>
ForwardList<T> &ForwardList<T>::operator=(const ForwardList<T> &other)
{
    if (this == &other)
        return *this;
    clear();
    copy(other);
    return *this;
}

template <typename T>
void ForwardList<T>::copy(const ForwardList<T> &other)
{
    if (!other.head)
        return;
    head = new ForwardListEl<T>(other.head->data);
    ForwardListEl<T> *thisIter = head, *otherIter = other.head->next;
    while (otherIter)
    {
        thisIter->next = new ForwardListEl<T>(otherIter->data);
        thisIter = thisIter->next;
        otherIter = otherIter->next;
    }
    tail = thisIter;
    mSize = other.mSize;
}

template <typename T>
ForwardList<T>::~ForwardList()
{
    clear();
}

template <typename T>
void ForwardList<T>::push_back(const T &data)
{
    if (!head)
    {
        head = tail = new ForwardListEl<T>(data);
        ++mSize;
        return;
    }
    ForwardListEl<T> *newEl = new ForwardListEl<T>(data);
    tail->next = newEl;
    tail = tail->next;
    ++mSize;
}

template <typename T>
void ForwardList<T>::pop_front()
{
    if (!head)
        throw std::runtime_error("empty ForwardList");
    ForwardListEl<T> *prev = head;
    if (tail == head)
        tail = nullptr;
    head = head->next;
    delete prev;
    --mSize;
}

template <typename T>
void ForwardList<T>::push_front(const T &data)
{
    if (!head)
    {
        head = tail = new ForwardListEl<T>(data);
        ++mSize;
        return;
    }
    ForwardListEl<T> *newEl = new ForwardListEl<T>(data);
    newEl->next = head;
    head = newEl;
    ++mSize;
}

template <typename T>
T ForwardList<T>::front() const
{
    if (!head)
        throw std::runtime_error("empty ForwardList");
    return head->data;
}

template <typename T>
T ForwardList<T>::back() const
{
    if (!head)
        throw std::runtime_error("empty ForwardList");
    return tail->data;
}

template <typename T>
typename ForwardList<T>::Iterator &ForwardList<T>::Iterator::operator++()
{
    ptr = ptr->next;
    return *this;
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++*this;
    return tmp;
}

template <typename T>
void ForwardList<T>::insertAfter(const Iterator &pos, const T &el)
{
    pos.ptr->next = new ForwardListEl<T>(el, pos.ptr->next);
    ++mSize;
}

template <typename T>
void ForwardList<T>::eraseAfter(Iterator &pos)
{
    if (!pos)
        return;
    if (pos->ptr == tail)
    {
        delete tail;
        tail = pos->ptr;
        --size;
        return;
    }
    Iterator tmp = pos++;
    tmp.ptr->next = pos.ptr->next;
    delete pos.ptr;
    pos = ++tmp;
    --size;
}

template <typename T>
void ForwardList<T>::clear()
{
    if (!head)
        return;
    tail = head;
    do
    {
        head = head->next;
        delete tail;
        tail = head;
    } while (head);
}

template <typename T>
void ForwardList<T>::swap(ForwardList &other)
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(mSize, other.mSize);
}

#endif