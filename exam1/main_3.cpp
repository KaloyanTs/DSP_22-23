#include <iostream>
#include <queue>
#include <stack>
#include <string>

bool canBeRead(std::queue<char> &q, const std::string &str)
{
    q.push('\n');
    bool read = true;
    for (const char &letter : str)
    {
        while (q.front() != '\n' && q.front() != letter)
        {
            q.push(q.front());
            q.pop();
        }
        if (q.front() == '\n')
        {
            read = false;
            break;
        }
        q.pop();
    }
    while (q.front() != '\n')
    {
        q.push(q.front());
        q.pop();
    }
    q.pop();
    std::stack<char> st;
    while (!q.empty())
    {
        st.push(q.front());
        q.pop();
    }
    while (!st.empty())
    {
        q.push(st.top());
        st.pop();
    }

    return read;
}

int main()
{
    std::string str1 = "mom";
    std::queue<char> q1;
    q1.push('m');
    q1.push('f');
    q1.push('o');
    q1.push('o');
    q1.push('m');

    std::cout << std::boolalpha << canBeRead(q1, str1) << '\n'
              << '\n';
    while (!q1.empty())
    {
        std::cout << q1.front() << '\n';
        q1.pop();
    }
    std::cout << '\n';

    std::string str2 = "car";
    std::queue<char> q2;
    q2.push('c');
    q2.push('c');
    q2.push('d');
    q2.push('a');
    q2.push('y');

    std::cout << std::boolalpha << canBeRead(q2, str2) << '\n';
    while (!q2.empty())
    {
        std::cout << q2.front() << '\n';
        q2.pop();
    }

    return 0;
}