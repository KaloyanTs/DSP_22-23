#include <cstddef>
#include <stdexcept>

template <typename T>
struct QueueEl
{
    T data;
    QueueEl *next;
    QueueEl(const T &d) : data(d), next(nullptr) {}
};

template <typename T>
struct queue
{
    QueueEl<T> *head, *tail;
    size_t size;
    queue() : head(nullptr), tail(nullptr), size(0) {}
    queue(const T &d) : head(new QueueEl<T>(d)), tail(head), size(1) {}
    queue(const queue &) = delete;
    queue &operator=(const queue &) = delete;
    void print() const;
    void push(const T &data);
    void pop();
    T front() const;
    bool empty() const { return !head; }
    size_t getSize() const { return size; }
    ~queue();
};

template <typename T>
void queue<T>::print() const
{
    QueueEl<T> *end = head;
    while (end)
    {
        std::cout << end->data << '\n';
        end = end->next;
    }
    std::cout << '\n';
}

template <typename T>
queue<T>::~queue()
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
void queue<T>::push(const T &data)
{
    if (!head)
    {
        head = tail = new QueueEl<T>(data);
        ++size;
        return;
    }
    QueueEl<T> *newEl = new QueueEl<T>(data);
    tail->next = newEl;
    tail = tail->next;
    ++size;
}

template <typename T>
void queue<T>::pop()
{
    if (!head)
        throw std::runtime_error("empty queue");
    QueueEl<T> *prev = head;
    if (tail == head)
        tail = nullptr;
    head = head->next;
    delete prev;
    --size;
}

template <typename T>
T queue<T>::front() const
{
    if (!head)
        throw std::runtime_error("empty queue");
    return head->data;
}