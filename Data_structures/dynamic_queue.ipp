#ifndef __DYNAMIC_QUEUE_IPP
#define __DYNAMIC_QUEUE_IPP
#include <cstddef>
#include <exception>
//todo
template <typename T>
class DynamicQueue
{
    static const size_t INIT_CAP = 4;
    T *arr;
    size_t mCap, mSize;
    void copy(const DynamicQueue &other);
    void clear();
    void shrink();
    void expand();

public:
    DynamicQueue() : mSize(0), arr(new T[INIT_CAP]), mCap(INIT_CAP) {}
    DynamicQueue(const DynamicQueue &other);
    DynamicQueue &operator=(const DynamicQueue &other);
    ~DynamicQueue();
    bool empty() const { return !mSize; }
    const T &top() const;
    T &top();
    size_t size() const { return mSize; };
    void push(T &&value);
    void push(const T &value);
    void pop();
    void swap(DynamicQueue &other);
};

template <typename T>
void DynamicQueue<T>::copy(const DynamicQueue<T> &other)
{
    mCap = mSize = other.mSize;
    arr = new T[mSize];
    for (unsigned i = 0; i < mSize; ++i)
        arr[i] = other.arr[i];
}
template <typename T>
void DynamicQueue<T>::clear()
{
    delete arr;
    arr = nullptr;
    mSize = mCap = 0;
}
template <typename T>
void DynamicQueue<T>::shrink()
{
    if (mCap <= INIT_CAP || mSize > (mCap >> 1))
        return;
    mCap >>= 1;
    T *newArr = new T[mCap];
    for (unsigned i = 0; i < mSize; ++i)
        newArr[i] = arr[i];
    delete arr;
    arr = newArr;
}
template <typename T>
void DynamicQueue<T>::expand()
{
    if (mSize < mCap)
        return;
    mCap <<= 1;
    T *newArr = new T[mCap];
    for (unsigned i = 0; i < mSize; ++i)
        newArr[i] = arr[i];
    delete arr;
    arr = newArr;
}

template <typename T>
DynamicQueue<T>::DynamicQueue(const DynamicQueue &other)
    : arr(nullptr), mSize(0)
{
    copy(other);
}

template <typename T>
DynamicQueue<T> &DynamicQueue<T>::operator=(const DynamicQueue<T> &other)
{
    if (this == &other)
        return *this;
    clear();
    copy(other);
    return *this;
}

template <typename T>
DynamicQueue<T>::~DynamicQueue()
{
    clear();
}

template <typename T>
const T &DynamicQueue<T>::top() const
{
    if (empty())
        throw std::logic_error("the stack is empty...");
    return arr[mSize - 1];
}

template <typename T>
T &DynamicQueue<T>::top()
{
    if (empty())
        throw std::runtime_error("the stack is empty...");
    return arr[mSize - 1];
}

template <typename T>
void DynamicQueue<T>::push(T &&value)
{
    expand();
    arr[mSize++] = value;
}

template <typename T>
void DynamicQueue<T>::push(const T &value)
{
    expand();
    arr[mSize++] = value;
}

template <typename T>
void DynamicQueue<T>::pop()
{
    if (empty())
        throw std::runtime_error("the stack is empty...");
    --mSize;
    shrink();
}

template <typename T>
void DynamicQueue<T>::swap(DynamicQueue &other)
{
    std::swap(arr, other.arr);
    std::swap(mSize, other.mSize);
    std::swap(mCap, other.mCap);
}

#endif