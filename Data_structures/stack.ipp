#include <cstddef>
#include <stdexcept>

template <typename T>
struct StackEl
{
    T data;
    StackEl *next;
    StackEl(const T &d) : data(d), next(nullptr) {}
};

template <typename T>
struct stack
{
    StackEl<T> *head;
    size_t size;
    stack() : head(nullptr), size(0) {}
    stack(const T &d) : head(new StackEl<T>(d)), size(1) {}
    stack(const stack &) = delete;
    stack &operator=(const stack &) = delete;
    void print() const;
    void push(const T &data);
    void pop();
    T top() const;
    bool empty() const { return !head; }
    size_t getSize() const { return size; }
    ~stack();
};

template <typename T>
void stack<T>::print() const
{
    StackEl<T> *end = head;
    while (end)
    {
        std::cout << end->data << '\n';
        end = end->next;
    }
    std::cout << '\n';
}

template <typename T>
stack<T>::~stack()
{
    if (!head)
        return;
    StackEl<T> *prev = head;
    do
    {
        head = head->next;
        delete prev;
        prev = head;
    } while (head);
}

template <typename T>
void stack<T>::push(const T &data)
{
    if (!head)
    {
        head = new StackEl<T>(data);
        ++size;
        return;
    }
    StackEl<T> *newEl = new StackEl<T>(data);
    newEl->next = head;
    head = newEl;
    ++size;
}

template <typename T>
void stack<T>::pop()
{
    if (!head)
        throw std::runtime_error("empty stack");
    StackEl<T> *prev = head;
    head = head->next;
    delete prev;
    --size;
}

template <typename T>
T stack<T>::top() const
{
    if (!head)
        throw std::runtime_error("empty stack");
    return head->data;
}