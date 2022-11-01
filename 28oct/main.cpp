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

using Pos = std::pair<int, int>;
using Path = std::vector<Pos>;

bool isValid(const Pos &p, bool home[][HOME_WIDTH])
{
    return p.first >= 0 &&
           p.second >= 0 &&
           p.first < HOME_WIDTH &&
           p.second < HOME_HEIGHT &&
           !home[p.first][p.second];
}

void printPath(const Path &path)
{
    for (unsigned i = 0; i < path.size(); ++i)
    {
        if (i)
            std::cout << " -> ";
        std::cout << '(' << path.at(i).first << ", " << path.at(i).second << ')';
    }
    std::cout << '\n';
}

Path saveJerry(bool home[][HOME_WIDTH])
{
    std::queue<Path> v;
    Path start;
    start.push_back({0, 0});
    v.push(start);
    Path current, nextCur;
    Pos curPos;
    while (!v.empty())
    {
        current = v.front();
        curPos = current.back();
        v.pop();
        if (curPos == Pos(HOME_HEIGHT - 1, HOME_WIDTH - 1))
            return current;
        home[curPos.first][curPos.second] = true;
        for (int i : {-1, 1})
        {
            if (isValid({curPos.first, curPos.second + i}, home) &&
                !home[curPos.first][curPos.second + i])
            {
                current.push_back({curPos.first, curPos.second + i});
                v.push(current);
                current.pop_back();
            }
            if (isValid({curPos.first + i, curPos.second}, home) &&
                !home[curPos.first + i][curPos.second])
            {
                current.push_back({curPos.first + i, curPos.second});
                v.push(current);
                current.pop_back();
            }
        }
    }
    return Path();
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
    // qStack<int> st;
    // st.push(1);
    // st.push(2);
    // st.push(3);
    // st.push(4);
    // while (!st.empty())
    // {
    //     std::cout << st.top() << ' ';
    //     st.pop();
    // }
    // std::cout << '\n';
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

    bool home[HOME_HEIGHT][HOME_WIDTH] =
        {
            {0, 1, 0, 0, 0, 0, 1, 1, 0, 1},
            {0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
            {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
            {1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        };

    Path path = saveJerry(home);
    if (path.size())
    {
        std::cout << "Jerry is saved:\n";
        printPath(path);
    }
    else
        std::cout << "Sorry, Jerry ;(\n";

    return 0;
}