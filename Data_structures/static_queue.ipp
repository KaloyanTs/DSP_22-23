#ifndef __STATIC_QUEUE_IPP
#define __STATIC_QUEUE_IPP
#include <cstddef>
#include <exception>

template <typename T>
class StaticQueue
{
    static const size_t MAX_SIZE = 64;
    T arr[MAX_SIZE];
    int mFront, mBack;

public:
    StaticQueue() : mFront(0), mBack(0) {}
    StaticQueue(const StaticQueue &other) = default;
    StaticQueue &operator=(const StaticQueue &other) = default;
    ~StaticQueue() = default;
    bool empty() const { return mBack == mFront; }
    const T &front() const;
    T &front();
    size_t size() const { return (mBack - mFront + MAX_SIZE) % MAX_SIZE; }
    void push(const T &value);
    void push(T &&value);
    void pop();
    void swap(StaticQueue &other);
};
template <typename T>
const T &StaticQueue<T>::front() const
{
    if (empty())
        throw std::logic_error("the queue is empty...");
    return arr[mFront];
}
template <typename T>
T &StaticQueue<T>::front()
{
    if (empty())
        throw std::runtime_error("the queue is empty...");
    return arr[mFront];
}
template <typename T>
void StaticQueue<T>::push(const T &value)
{
    if ((mFront - mBack - 1) % MAX_SIZE == 0)
        throw std::runtime_error("queue overflow...");
    arr[mBack++] = value;
    mBack %= MAX_SIZE;
}
template <typename T>
void StaticQueue<T>::push(T &&value)
{
    if ((mFront - mBack - 1) % MAX_SIZE == 0)
        throw std::runtime_error("queue overflow...");
    arr[mBack++] = value;
    mBack %= MAX_SIZE;
}
template <typename T>
void StaticQueue<T>::pop()
{
    if (empty())
        throw std::runtime_error("the queue is empty...");
    mFront = (mFront + 1) % MAX_SIZE;
}
template <typename T>
void StaticQueue<T>::swap(StaticQueue<T> &other)
{
    std::swap(arr, other.arr);
    std::swap(mFront, other.mFront);
    std::swap(mBack, other.mBack);
}

#endif