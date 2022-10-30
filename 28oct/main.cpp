#include <iostream>
#include <queue>
#include <stack>
#include <utility>

const unsigned HOME_WIDTH = 2;
const unsigned HOME_HEIGHT = 2;

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

using pos = std::pair<unsigned, unsigned>;
std::stack<pos> saveJerry(bool home[][HOME_WIDTH])
{
    struct visCell
    {
        pos prev;
        pos current;
        visCell(const pos &c = {0, 0}, const pos &p = {-1, -1}) : prev(p), current(c) {}
    };
    std::queue<visCell> q;
    std::stack<visCell> past;

    q.push(visCell());
    visCell c;
    while (!q.empty())
    {
        c = q.front();
        q.pop();
        if (c.current == pos({HOME_WIDTH - 1, HOME_HEIGHT - 1}))
        {
            std::stack<pos> res;
            res.push(c.current);
            res.push(c.prev);
            while (!past.empty())
            {
                while (c.prev.first != -1 && c.prev.second != -1 && past.top().current != c.prev)
                {
                    std::cout << '(' << past.top().current.first << ',' << past.top().current.second << ')' << ' ';
                    past.pop();
                }
                c.prev = past.top().prev;
                past.pop();
                res.push(c.prev);
            }
            return res;
        }
        if (!(c.current.first < 0 || c.current.first >= HOME_WIDTH ||
              c.current.second < 0 || c.current.second >= HOME_HEIGHT ||
              home[c.current.first][c.current.second]))
        {
            home[c.current.first][c.current.second] = true;
            past.push(c);
            c.prev = c.current;
            for (int dx = -1; dx <= 1; dx += 2)
                for (int dy = -1; dy <= 1; dy += 2)
                    q.push(pos({c.current.first + dx, c.current.second + dy}));
        }
    }
    return std::stack<pos>();
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

    // bool home[HOME_HEIGHT][HOME_WIDTH] =
    //     {
    //         {0, 1, 0, 0, 0, 0, 1, 1, 0, 1},
    //         {0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
    //         {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    //         {1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
    //         {0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    //         {1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    //         {0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    //         {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
    //         {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
    //         {1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    //     };

    bool home[HOME_HEIGHT][HOME_WIDTH] =
        {
            {0, 1},
            {0, 0},
        };

    std::stack<pos> path = saveJerry(home);
    while (!path.empty())
    {
        std::cout << '(' << path.top().first << ',' << path.top().second << ')';
        path.pop();
        if (!path.empty())
            std::cout << " -> ";
    }
    std::cout << '\n';

    return 0;
}