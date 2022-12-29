#ifndef __STATIC_STACK_IPP
#define __STATIC_STACK_IPP
#include <cstddef>
#include <exception>

template <typename T>
class StaticStack
{
    static const size_t MAX_SIZE = 64;
    T arr[MAX_SIZE];
    size_t mSize;

public:
    StaticStack() : mSize(0) {}
    StaticStack(const StaticStack &other) = default;
    StaticStack &operator=(const StaticStack &other) = default;
    ~StaticStack() = default;
    bool empty() const { return !mSize; }
    const T &top() const;
    T &top();
    size_t size() const { return mSize; }
    void push(const T &value);
    void push(T &&value);
    void pop();
    void swap(StaticStack &other);
};
template <typename T>
const T &StaticStack<T>::top() const
{
    if (empty())
        throw std::logic_error("the stack is empty...");
    return arr[mSize - 1];
}
template <typename T>
T &StaticStack<T>::top()
{
    if (empty())
        throw std::runtime_error("the stack is empty...");
    return arr[mSize - 1];
}
template <typename T>
void StaticStack<T>::push(const T &value)
{
    if (mSize >= MAX_SIZE)
        throw std::runtime_error("stack overflow...");
    arr[mSize++] = value;
}
template <typename T>
void StaticStack<T>::push(T &&value)
{
    if (mSize >= MAX_SIZE)
        throw std::runtime_error("stack overflow...");
    arr[mSize++] = value;
}
template <typename T>
void StaticStack<T>::pop()
{
    if (empty())
        throw std::runtime_error("the stack is empty...");
    --mSize;
}
template <typename T>
void StaticStack<T>::swap(StaticStack<T> &other)
{
    std::swap(arr, other.arr);
    std::swap(mSize, other.mSize);
}

#endif