#include <iostream>
#include <stack>

bool isOpeningBracket(char c)
{
    return c == '(' || c == '{' || c == '[';
}

bool isClosingBracket(char c)
{
    return c == ')' || c == '}' || c == ']';
}

bool areMatching(char a, char b)
{
    return (a == '(' && b == ')') ||
           (a == '[' && b == ']') ||
           (a == '{' && b == '}');
}

bool checkBrackets(const char *expr)
{
    std::stack<char> buf;
    while (*expr)
    {
        if (isOpeningBracket(*expr))
            buf.push(*expr);
        else if (isClosingBracket(*expr))
            if (buf.empty() || !areMatching(buf.top(), *expr))
                return false;
            else
                buf.pop();
        ++expr;
    }
    return buf.empty();
}

void hanoi(unsigned n, char from, char to, char empty)
{
    if (n == 1)
    {
        std::cout << from << " -> " << to << '\n';
        return;
    }
    hanoi(n - 1, from, empty, to);
    std::cout << from << " -> " << to << '\n';
    hanoi(n - 1, empty, to, from);
}

void hanoiStack(unsigned n, char from, char to, char empty)
{
    struct Move
    {
        unsigned small, big;
        char from, to, empty;
        Move(unsigned s, unsigned b, char f, char t, char e) : small(s), big(b), from(f), to(t), empty(e) {}
    };
    std::stack<Move> buf;
    buf.push(Move(1, n, from, to, empty));
    Move current(0, 0, 0, 0, 0);
    while (!buf.empty())
    {
        current = buf.top();
        buf.pop();
        if (current.small == current.big)
            std::cout << current.from << " -> " << current.to << '\n';
        else
        {
            buf.push(Move(current.small, current.big - 1, current.empty, current.to, current.from));
            buf.push(Move(current.big, current.big, current.from, current.to, current.empty));
            buf.push(Move(current.small, current.big - 1, current.from, current.empty, current.to));
        }
    }
}

char *reverseStringStack(char *str)
{
    std::stack<char> buf;
    char *i = str;
    while (*i)
        buf.push(*i++);
    i = str;
    while (!buf.empty())
    {
        *str++ = buf.top();
        buf.pop();
    }
    return i;
}

std::stack<int> mergeStacks(std::stack<int> &a, std::stack<int> &b)
{
    std::stack<int> res;
    while (!a.empty() && !b.empty())
    {
        if (a.top() > b.top())
            res.push(b.top());
        else
            res.push(b.top());
        a.pop();
        b.pop();
    }
    while (!a.empty())
    {
        res.push(a.top());
        a.pop();
    }
    while (!b.empty())
    {
        res.push(b.top());
        b.pop();
    }
    while (!res.empty())
    {
        a.push(res.top());
        res.pop();
    }
    return a;
}

void sortStack(std::stack<int> &st)
{
    std::stack<int> buf;
    std::stack<int> tmp;
    while (!st.empty())
    {
        while (!st.empty() && (buf.empty() || buf.top() > st.top()))
        {
            buf.push(st.top());
            st.pop();
        }
        if (st.empty())
        {
            st = buf;
            return;
        }
        while (!buf.empty() && buf.top() <= st.top())
        {
            tmp.push(buf.top());
            buf.pop();
        }
        buf.push(st.top());
        st.pop();
        while (!tmp.empty())
        {
            buf.push(tmp.top());
            tmp.pop();
        }
    }
    st = buf;
};

int main()
{
    const char *expr = "(3+6) / {54g( p3[jw ][])}";
    std::cout << checkBrackets(expr) << '\n';
    hanoi(4, 'A', 'B', 'C');
    std::cout << "-----Using stack-----\n";
    hanoiStack(4, 'A', 'B', 'C');
    char str[] = "Hello world!";
    std::cout << reverseStringStack(str) << '\n';
    std::stack<int> s;
    s.push(3);
    s.push(6);
    s.push(4);
    s.push(1);
    s.push(5);
    s.push(2);
    sortStack(s);
    while (!s.empty())
    {
        std::cout << s.top() << ' ';
        s.pop();
    }
    return 0;
}