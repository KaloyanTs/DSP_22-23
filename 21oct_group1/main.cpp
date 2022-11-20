#include <iostream>
#include <string>

struct el
{
    std::string val;
    el *next;
    el(const std::string &_val, el *n = nullptr)
        : val(_val), next(n) {}
};

struct stack
{
    el *head;
    stack() : head(nullptr) {}
    void push(const std::string &s)
    {
        head = new el(s, head);
    }
    std::string pop()
    {
        if (!head)
            throw std::runtime_error("empty queue");
        el *tmp = head;
        head = head->next;
        std::string res = tmp->val;
        delete tmp;
        return res;
    }
    bool empty() const { return !head; }
    const std::string &front()
    {
        if (!head)
            throw std::runtime_error("empty stack");
        return head->val;
    }
    void clear()
    {
        el *prev = head;
        while (head)
        {
            head = head->next;
            delete prev;
            prev = head;
        }
    }
    ~stack()
    {
        clear();
    }
};

bool isDigit(char c)
{
    return (c - '0') >= 0 && (c - '0') <= 9;
}

void decompress(const std::string &s)
{
    stack st;
    std::string res = "";
    std::string current;
    char *str;
    st.push(s);
    while (!st.empty())
    {
        current = st.pop();
        str = (char *)current.c_str();
        while (*str)
        {
            if (str[1] == '(')
            {
                unsigned rep = *str - '0';
                str += 2;
                char *end = str;
                int balance = 0;
                while (*end != ')' || balance)
                {
                    if (*end == '(')
                        ++balance;
                    else if (*end == ')')
                        --balance;
                    ++end;
                }
                *end = '\0';
                for (unsigned i = 0; i < rep; ++i)
                {
                    st.push(str);
                }
                *end = ')';
                str = end + 1;
            }
            else
                res += *str++;
        }
    }
    std::cout << res << '\n';
}

int main()
{
    decompress("A");
    decompress("AB");
    decompress("3(A)");
    decompress("3(AB2(B))");
    return 0;
}