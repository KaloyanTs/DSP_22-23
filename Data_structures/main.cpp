#include <iostream>
#include "stack.ipp"
#include "queue.ipp"

int main()
{
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(6);
    st.push(5);
    st.push(3);
    std::cout << st.top() << '\n';

    while (!st.empty())
    {
        std::cout << st.top() << ' ';
        st.pop();
    }
    std::cout << '\n';

    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(6);
    q.push(5);
    q.push(3);
    std::cout << q.front() << '\n';

    while (!q.empty())
    {
        std::cout << q.front() << ' ';
        q.pop();
    }
    std::cout << '\n';

    return 0;
}