#ifndef __LIST_HPP
#define __LIST_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
struct ListEl
{
    T data;
    ListEl *next, *prev;
    ListEl(const T &d, ListEl *_prev = nullptr, ListEl *_next = nullptr)
        : data(d), next(_next), prev(_prev) {}
};

template <typename T>
struct List
{
public:
    class Iterator
    {
        ListEl<T> *ptr;

    public:
        Iterator(ListEl<T> *_ptr = nullptr) : ptr(_ptr) {}
        T &operator*() { return ptr->data; }
        Iterator &operator++();
        Iterator &operator--();
        Iterator operator--(int);
        Iterator operator++(int);
        bool operator==(const Iterator &other) { return ptr == other.ptr; }
        bool operator!=(const Iterator &other) { return ptr != other.ptr; }
        operator bool() { return ptr; }
        friend class List<T>;
    };
    class ReverseIterator
    {
        ListEl<T> *ptr;

    public:
        ReverseIterator(ListEl<T> *_ptr = nullptr) : ptr(_ptr) {}
        T &operator*() { return ptr->data; }
        ReverseIterator &operator++();
        ReverseIterator &operator--();
        ReverseIterator operator--(int);
        ReverseIterator operator++(int);
        bool operator==(const ReverseIterator &other) { return ptr == other.ptr; }
        bool operator!=(const ReverseIterator &other) { return ptr != other.ptr; }
        operator bool() { return ptr; }
        friend class List<T>;
    };

private:
    ListEl<T> *head, *tail;
    size_t mSize;
    void copy(const List<T> &other);

public:
    List() : head(nullptr), tail(nullptr), mSize(0) {}
    List(const T &d) : head(new ListEl<T>(d)), tail(head), mSize(1) {}
    List(const List &);
    List &operator=(const List &);
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
    ReverseIterator rbegin() const { return ReverseIterator(tail); }
    ReverseIterator rend() const { return ReverseIterator(nullptr); }
    void push_front(const T &data);
    void push_back(const T &data);
    void pop_front();
    void pop_back();
    T front() const;
    T back() const;
    bool empty() const { return !head; }
    size_t size() const { return mSize; }
    void insertAfter(const Iterator &pos, const T &el);
    void eraseAfter(Iterator &pos);
    void clear();
    void swap(List &other);
    ~List();
};

template <typename T>
List<T>::List(const List<T> &other)
    : head(nullptr), tail(nullptr)
{
    copy(other);
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &other)
{
    if (this == &other)
        return *this;
    clear();
    copy(other);
    return *this;
}

template <typename T>
void List<T>::copy(const List<T> &other)
{
    if (!other.head)
        return;
    head = new ListEl<T>(other.head->data);
    ListEl<T> *thisIter = head, *otherIter = other.head->next;
    while (otherIter)
    {
        thisIter->next = new ListEl<T>(otherIter->data, thisIter);
        thisIter = thisIter->next;
        otherIter = otherIter->next;
    }
    tail = thisIter;
    mSize = other.mSize;
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
void List<T>::push_back(const T &data)
{
    if (!head)
    {
        head = tail = new ListEl<T>(data);
        ++mSize;
        return;
    }
    ListEl<T> *newEl = new ListEl<T>(data, tail);
    tail->next = newEl;
    tail = tail->next;
    ++mSize;
}

template <typename T>
void List<T>::pop_front()
{
    if (!head)
        throw std::runtime_error("empty List");
    ListEl<T> *pr = head;
    if (tail == head)
        tail = nullptr;
    head = head->next;
    delete pr;
    --mSize;
}

template <typename T>
void List<T>::pop_back()
{
    if (!tail)
        throw std::runtime_error("empty List");
    ListEl<T> *pr = tail;
    if (tail == head)
        head = nullptr;
    tail = tail->prev;
    delete pr;
    --mSize;
}

template <typename T>
void List<T>::push_front(const T &data)
{
    if (!head)
    {
        head = tail = new ListEl<T>(data);
        ++mSize;
        return;
    }
    ListEl<T> *newEl = new ListEl<T>(data, nullptr, head);
    head->prev = newEl;
    head = newEl;
    ++mSize;
}

template <typename T>
T List<T>::front() const
{
    if (!head)
        throw std::runtime_error("empty List");
    return head->data;
}

template <typename T>
T List<T>::back() const
{
    if (!head)
        throw std::runtime_error("empty List");
    return tail->data;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++()
{
    ptr = ptr->next;
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++*this;
    return tmp;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator--()
{
    ptr = ptr->prev;
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
    Iterator tmp = *this;
    --*this;
    return tmp;
}

template <typename T>
typename List<T>::ReverseIterator &List<T>::ReverseIterator::operator++()
{
    ptr = ptr->prev;
    return *this;
}

template <typename T>
typename List<T>::ReverseIterator List<T>::ReverseIterator::operator++(int)
{
    Iterator tmp = *this;
    ++*this;
    return tmp;
}

template <typename T>
typename List<T>::ReverseIterator &List<T>::ReverseIterator::operator--()
{
    ptr = ptr->next;
    return *this;
}

template <typename T>
typename List<T>::ReverseIterator List<T>::ReverseIterator::operator--(int)
{
    Iterator tmp = *this;
    --*this;
    return tmp;
}

template <typename T>
void List<T>::insertAfter(const Iterator &pos, const T &el)
{
    pos.ptr->next = new ListEl<T>(el, pos.ptr, pos.ptr->next);
    ++mSize;
}

template <typename T>
void List<T>::eraseAfter(Iterator &pos)
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
    tmp.ptr->next->prev = tmp.ptr;
    delete pos.ptr;
    pos = ++tmp;
    --size;
}

template <typename T>
void List<T>::clear()
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
void List<T>::swap(List &other)
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(mSize, other.mSize);
}

#endif