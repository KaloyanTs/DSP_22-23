#ifndef __LIST_HPP
#define __LIST_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
struct ListEl
{
    T data;
    ListEl *next;
    ListEl(const T &d) : data(d), next(nullptr) {}
};

template <typename T>
struct list
{
    ListEl<T> *head, *tail;
    size_t size;
    list() : head(nullptr), tail(nullptr), size(0) {}
    list(const T &d) : head(new ListEl<T>(d)), tail(head), size(1) {}
    list(const list &) = delete;
    list &operator=(const list &) = delete;
    void print() const;
    void push_front(const T &data);
    void push_back(const T &data);
    void pop_front();
    T front() const;
    T back() const;
    bool empty() const { return !head; }
    size_t getSize() const { return size; }
    ~list();
};

template <typename T>
void list<T>::print() const
{
    ListEl<T> *end = head;
    while (end)
    {
        std::cout << end->data << '\n';
        end = end->next;
    }
    std::cout << '\n';
}

template <typename T>
list<T>::~list()
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
void list<T>::push_back(const T &data)
{
    if (!head)
    {
        head = tail = new ListEl<T>(data);
        ++size;
        return;
    }
    ListEl<T> *newEl = new ListEl<T>(data);
    tail->next = newEl;
    tail = tail->next;
    ++size;
}

template <typename T>
void list<T>::pop_front()
{
    if (!head)
        throw std::runtime_error("empty list");
    ListEl<T> *prev = head;
    if (tail == head)
        tail = nullptr;
    head = head->next;
    delete prev;
    --size;
}

template <typename T>
void list<T>::push_front(const T &data)
{
    if (!head)
    {
        head = tail = new StackEl<T>(data);
        ++size;
        return;
    }
    StackEl<T> *newEl = new StackEl<T>(data);
    newEl->next = head;
    head = newEl;
    ++size;
}

template <typename T>
T list<T>::front() const
{
    if (!head)
        throw std::runtime_error("empty list");
    return head->data;
}

template <typename T>
T list<T>::back() const
{
    if (!head)
        throw std::runtime_error("empty list");
    return tail->data;
}

#endif