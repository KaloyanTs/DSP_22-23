#ifndef __LINKED_STACK_HPP
#define __LINKED_STACK_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
struct LinkedStackEl
{
    T data;
    LinkedStackEl *next;
    LinkedStackEl(const T &d) : data(d), next(nullptr) {}
};

template <typename T>
class LinkedStack
{
    LinkedStackEl<T> *head;
    size_t mSize;
    void copy(const LinkedStack &other);
    void clear();

public:
    LinkedStack() : head(nullptr), mSize(0) {}
    LinkedStack(const T &d) : head(new LinkedStackEl<T>(d)), mSize(1) {}
    LinkedStack(const LinkedStack &);
    LinkedStack &operator=(const LinkedStack &);
    void push(const T &data);
    void pop();
    T &top();
    const T &top() const;
    bool empty() const { return !head; }
    size_t size() const { return mSize; }
    void swap(LinkedStack &);
    ~LinkedStack();
};

template <typename T>
void LinkedStack<T>::copy(const LinkedStack<T> &other)
{
    mSize = other.mSize;
    if (!other.head)
    {
        head = nullptr;
        return;
    }
    LinkedStackEl<T> *thisIter, *otherIter = other.head;
    head = thisIter = new LinkedStackEl<T>(otherIter->data);
    while (otherIter->next)
    {
        otherIter = otherIter->next;
        thisIter->next = new LinkedStackEl<T>(otherIter->data);
        thisIter = thisIter->next;
    }
}

template <typename T>
void LinkedStack<T>::clear()
{
    if (!head)
        return;
    LinkedStackEl<T> *prev = head;
    do
    {
        head = head->next;
        delete prev;
        prev = head;
    } while (head);
}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack &other)
    : head(nullptr)
{
    copy(other);
}

template <typename T>
LinkedStack<T> &LinkedStack<T>::operator=(const LinkedStack<T> &other)
{
    if (this == &other)
        return *this;
    clear();
    copy(other);
    return *this;
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    clear();
}

template <typename T>
void LinkedStack<T>::push(const T &data)
{
    if (!head)
    {
        head = new LinkedStackEl<T>(data);
        ++mSize;
        return;
    }
    LinkedStackEl<T> *newEl = new LinkedStackEl<T>(data);
    newEl->next = head;
    head = newEl;
    ++mSize;
}

template <typename T>
void LinkedStack<T>::pop()
{
    if (!head)
        throw std::runtime_error("empty LinkedStack");
    LinkedStackEl<T> *prev = head;
    head = head->next;
    delete prev;
    --mSize;
}

template <typename T>
T &LinkedStack<T>::top()
{
    if (!head)
        throw std::runtime_error("empty LinkedStack");
    return head->data;
}

template <typename T>
const T &LinkedStack<T>::top() const
{
    if (!head)
        throw std::runtime_error("empty LinkedStack");
    return head->data;
}

template <typename T>
void LinkedStack<T>::swap(LinkedStack<T> &other)
{
    std::swap(head, other.head);
    std::swap(mSize, other.mSize);
}

#endif