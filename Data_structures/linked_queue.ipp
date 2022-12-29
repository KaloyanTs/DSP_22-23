#ifndef __LINKED_QUEUE_HPP
#define __LINKED_QUEUE_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
struct LinkedQueueEl
{
    T data;
    LinkedQueueEl *next;
    LinkedQueueEl(const T &d) : data(d), next(nullptr) {}
};

template <typename T>
struct LinkedQueue
{
    LinkedQueueEl<T> *head, *tail;
    size_t size;
    LinkedQueue() : head(nullptr), tail(nullptr), size(0) {}
    LinkedQueue(const T &d) : head(new LinkedQueueEl<T>(d)), tail(head), size(1) {}
    LinkedQueue(const LinkedQueue &) = delete;
    LinkedQueue &operator=(const LinkedQueue &) = delete;
    void print() const;
    void push(const T &data);
    void pop();
    T front() const;
    bool empty() const { return !head; }
    size_t getSize() const { return size; }
    ~LinkedQueue();
};

template <typename T>
void LinkedQueue<T>::print() const
{
    LinkedQueueEl<T> *end = head;
    while (end)
    {
        std::cout << end->data << '\n';
        end = end->next;
    }
    std::cout << '\n';
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
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
void LinkedQueue<T>::push(const T &data)
{
    if (!head)
    {
        head = tail = new LinkedQueueEl<T>(data);
        ++size;
        return;
    }
    LinkedQueueEl<T> *newEl = new LinkedQueueEl<T>(data);
    tail->next = newEl;
    tail = tail->next;
    ++size;
}

template <typename T>
void LinkedQueue<T>::pop()
{
    if (!head)
        throw std::runtime_error("empty LinkedQueue");
    LinkedQueueEl<T> *prev = head;
    if (tail == head)
        tail = nullptr;
    head = head->next;
    delete prev;
    --size;
}

template <typename T>
T LinkedQueue<T>::front() const
{
    if (!head)
        throw std::runtime_error("empty LinkedQueue");
    return head->data;
}

#endif