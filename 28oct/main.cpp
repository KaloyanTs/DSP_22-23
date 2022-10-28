#include <iostream>
#include <queue>
#include <stack>
#include <utility>

const unsigned HOME_WIDTH = 10;
const unsigned HOME_HEIGHT = 10;

template <typename T>
struct qStack
{
    std::queue<T> q;

public:
    bool empty() const { return q.empty(); }
    void push(const T &el)
    {
        T tmp;
        q.push(el);
        for (unsigned i = 0; i < q.size() - 1; ++i)
        {
            tmp = q.front();
            q.pop();
            q.push(tmp);
        }
    }
    T top()
    {
        return q.front();
    }
    void pop()
    {
        q.pop();
    }
};

template <typename T>
struct stQueue
{
    std::stack<T> st;

public:
    void pop()
    {
        if (st.size() == 1)
        {
            st.pop();
            return;
        }
        T tmp = st.top();
        st.pop();
        this->pop();
        st.push(tmp);
    }
    T front()
    {
        if (st.size() == 1)
            return st.top();
        T tmp = st.top();
        st.pop();
        T res = this->front();
        st.push(tmp);
        return res;
    }
    bool empty() const
    {
        return st.empty();
    }
    void push(const T &el)
    {
        st.push(el);
    }
};

template <typename T>
bool isSorted(std::queue<T> &q)
{
    if (q.size() < 3)
        return true;
    bool res = true;
    T first;
    for (unsigned i = 0; i < q.size() - 1; ++i)
    {
        first = q.front();
        q.pop();
        if (res && first < q.front())
            res = false;
        q.push(first);
    }
    first = q.front();
    q.pop();
    q.push(first);
    return res;
}

unsigned ArthurIsCoward(unsigned n)
{
    if (n == 1)
        return 1;
    std::queue<unsigned> q;
    for (unsigned i = 1; i <= n; ++i)
        q.push(i);
    unsigned current;
    while (q.size() > 1)
    {
        current = q.front();
        q.pop();
        q.pop();
        q.push(current);
    }
    return q.front();
}

std::queue<std::pair<unsigned, unsigned>> saveJerry(unsigned n, unsigned m)
{

    std::queue<std::queue<std::pair<unsigned, unsigned>>> paths;
    std::queue<std::pair<unsigned, unsigned>> curPath;
    // curPath.push({0, 0});
    // paths.push(curPath);
    // while (!paths.empty())
    // {
    //     curPath = paths.front();
    //     if (curPath.front() == std::pair<unsigned, unsigned>({n - 1, m - 1}))
    //         return curPath;
    //     paths.pop();
    //     for (unsigned dx = -1; dx <= 1; dx += 2)
    //         for (unsigned dy = -1; dy <= 1; dy += 2)
    //         {
    //             curPath.push({})
    //         }
    // }
    return paths.front();
}

int main()
{
    std::queue<int> q;
    q.push(11);
    q.push(10);
    q.push(5);
    q.push(4);
    q.push(2);
    std::cout << std::boolalpha << isSorted(q) << '\n';
    qStack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    while (!st.empty())
    {
        std::cout << st.top() << ' ';
        st.pop();
    }
    std::cout << '\n';
    std::cout << "From 10 knights Arthur should be on position No " << ArthurIsCoward(10) << '\n';

    stQueue<int> stQ;
    stQ.push(1);
    stQ.push(2);
    stQ.push(3);
    stQ.push(4);
    stQ.push(5);
    while (!stQ.empty())
    {
        std::cout << stQ.front() << ' ';
        stQ.pop();
    }
    std::cout << '\n';
    return 0;
}