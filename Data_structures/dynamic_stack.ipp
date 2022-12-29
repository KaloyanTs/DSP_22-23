#ifndef __DYNAMIC_STACK_IPP
#define __DYNAMIC_STACK_IPP
#include <cstddef>
#include <exception>

template <typename T>
class DynamicStack
{
    static const size_t INIT_CAP = 4;
    T *arr;
    size_t mCap, mSize;
    void copy(const DynamicStack &other);
    void clear();
    void shrink();
    void expand();

public:
    DynamicStack() : mSize(0), arr(new T[INIT_CAP]), mCap(INIT_CAP) {}
    DynamicStack(const DynamicStack &other);
    DynamicStack &operator=(const DynamicStack &other);
    ~DynamicStack();
    bool empty() const { return !mSize; }
    const T &top() const;
    T &top();
    size_t size() const { return mSize; };
    void push(T &&value);
    void push(const T &value);
    void pop();
    void swap(DynamicStack &other);
};

template <typename T>
void DynamicStack<T>::copy(const DynamicStack<T> &other)
{
    mCap = mSize = other.mSize;
    arr = new T[mSize];
    for (unsigned i = 0; i < mSize; ++i)
        arr[i] = other.arr[i];
}
template <typename T>
void DynamicStack<T>::clear()
{
    delete arr;
    arr = nullptr;
    mSize = mCap = 0;
}
template <typename T>
void DynamicStack<T>::shrink()
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
void DynamicStack<T>::expand()
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
DynamicStack<T>::DynamicStack(const DynamicStack &other)
    : arr(nullptr), mSize(0)
{
    copy(other);
}

template <typename T>
DynamicStack<T> &DynamicStack<T>::operator=(const DynamicStack<T> &other)
{
    if (this == &other)
        return *this;
    clear();
    copy(other);
    return *this;
}

template <typename T>
DynamicStack<T>::~DynamicStack()
{
    clear();
}

template <typename T>
const T &DynamicStack<T>::top() const
{
    if (empty())
        throw std::logic_error("the stack is empty...");
    return arr[mSize - 1];
}

template <typename T>
T &DynamicStack<T>::top()
{
    if (empty())
        throw std::runtime_error("the stack is empty...");
    return arr[mSize - 1];
}

template <typename T>
void DynamicStack<T>::push(T &&value)
{
    expand();
    arr[mSize++] = value;
}

template <typename T>
void DynamicStack<T>::push(const T &value)
{
    expand();
    arr[mSize++] = value;
}

template <typename T>
void DynamicStack<T>::pop()
{
    if (empty())
        throw std::runtime_error("the stack is empty...");
    --mSize;
    shrink();
}

template <typename T>
void DynamicStack<T>::swap(DynamicStack &other)
{
    std::swap(arr, other.arr);
    std::swap(mSize, other.mSize);
    std::swap(mCap, other.mCap);
}

#endif