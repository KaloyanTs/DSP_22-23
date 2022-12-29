#ifndef __STATIC_QUEUE_IPP
#define __STATIC_QUEUE_IPP
#include <cstddef>
#include <exception>
//todo
template <typename T>
class StaticQueue
{
    static const size_t MAX_SIZE = 64;
    T arr[MAX_SIZE];
    size_t mSize;

public:
    StaticQueue() : mSize(0) {}
    StaticQueue(const StaticQueue &other) = default;
    StaticQueue &operator=(const StaticQueue &other) = default;
    ~StaticQueue() = default;
    bool empty() const { return !mSize; }
    const T &top() const;
    T &top();
    size_t size() const { return mSize; }
    void push(const T &value);
    void push(T &&value);
    void pop();
    void swap(StaticQueue &other);
};
template <typename T>
const T &StaticQueue<T>::top() const
{
    if (empty())
        throw std::logic_error("the stack is empty...");
    return arr[mSize - 1];
}
template <typename T>
T &StaticQueue<T>::top()
{
    if (empty())
        throw std::runtime_error("the stack is empty...");
    return arr[mSize - 1];
}
template <typename T>
void StaticQueue<T>::push(const T &value)
{
    if (mSize >= MAX_SIZE)
        throw std::runtime_error("stack overflow...");
    arr[mSize++] = value;
}
template <typename T>
void StaticQueue<T>::push(T &&value)
{
    if (mSize >= MAX_SIZE)
        throw std::runtime_error("stack overflow...");
    arr[mSize++] = value;
}
template <typename T>
void StaticQueue<T>::pop()
{
    if (empty())
        throw std::runtime_error("the stack is empty...");
    --mSize;
}
template <typename T>
void StaticQueue<T>::swap(StaticQueue<T> &other)
{
    std::swap(arr, other.arr);
    std::swap(mSize, other.mSize);
}

#endif