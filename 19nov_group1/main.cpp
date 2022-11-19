#include <iostream>
#include <stdexcept>
#include <cstring>

struct Node
{
    int val;
    Node *next;
    Node(int _val, Node *_next) : val(_val), next(_next) {}
};

void clear(Node *head)
{
    Node *tmp = head;
    while (head)
    {
        head = head->next;
        delete tmp;
        tmp = head;
    }
}

void printList(Node *head)
{
    while (head)
    {
        std::cout << head->val << ' ';
        head = head->next;
    }
    std::cout << '\n';
}

void insertAfter(Node *pos, int val)
{
    pos->next = new Node(val, pos->next);
}

void shuffle(Node *&head)
{
    Node *fast = head, *slow = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *slowNext = slow->next;
    while (slowNext)
    {
        slow->next = slowNext->next;
        slowNext->next = head;
        head = slowNext;
        slowNext = slow->next;
    }
}

int reduce(Node *head, int (*op)(const int &, const int &))
{
    if (!head)
        throw std::logic_error("empty list");
    int res = head->val;
    head = head->next;
    while (head)
    {
        res = op(res, head->val);
        head = head->next;
    }
    return res;
}

int plus(const int &a, const int &b)
{
    return a + b;
}

void removeAll(Node *&head, int x)
{
    Node *iter = head;
    Node *prev = head;
    while (iter)
    {
        if (iter->val == x)
        {
            if (iter == prev)
            {
                head = head->next;
                delete iter;
                iter = prev = head;
            }
            else
            {
                prev->next = iter->next;
                delete iter;
                iter = prev->next;
            }
        }
        else
        {
            if (iter != prev)
                prev = prev->next;
            iter = iter->next;
        }
    }
}

bool duplicates(Node *head)
{
    Node *iter = head;

    while (head)
    {
        iter = head->next;
        while (iter && iter->val != head->val)
            iter = iter->next;
        if (iter)
            return true;
        head = head->next;
    }
    return false;
}

void reverse(Node *&head)
{
    if (!head || !head->next)
        return;
    Node *hNext = head->next, *prev = nullptr;
    while (hNext)
    {
        head->next = prev;
        prev = head;
        head = hNext;
        hNext = hNext->next;
    }
    head->next = prev;
}

bool palindrom(Node *head)
{
    Node *fast = head, *slow = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    reverse(slow);
    fast = slow;
    bool res;
    while (fast && fast->val == head->val)
    {
        head = head->next;
        fast = fast->next;
    }
    res = !fast;
    reverse(slow);
    return res;
}

struct FrogState
{
    char *state;
    FrogState(const char *_state = "")
        : state(new char[strlen(_state) + 1])
    {
        strcpy(state, _state);
    }
    FrogState(unsigned n)
        : state(new char[(n << 1) + 2])
    {
        unsigned i = 0;
        while (i < n)
            state[i++] = '<';
        state[i++] = ' ';
        while (i < (n << 1) + 1)
            state[i++] = '>';
        state[i] = '\0';
    }
    FrogState(const FrogState &other)
        : state(new char[strlen(other.state) + 1])
    {
        strcpy(state, other.state);
    }
    FrogState &operator=(const FrogState &other)
    {
        if (this == &other)
            return *this;
        delete state;
        state = new char[strlen(other.state) + 1];
        strcpy(state, other.state);
        return *this;
    };
    ~FrogState()
    {
        delete[] state;
    }
    bool validState() const { return state && state[0]; }
    FrogState nextStateJumpLeft() const
    {
        FrogState res(this->state);
        char *newState = res.state;
        while (*newState != ' ')
            ++newState;
        if (newState[1])
            if (newState[1] == '<')
            {
                newState[0] = '<';
                newState[1] = ' ';
                return res;
            }
            else if (newState[2] &&
                     newState[1] == '>' &&
                     newState[2] == '<')
            {
                newState[0] = '<';
                newState[2] = ' ';
                return res;
            }
        delete res.state;
        res.state = new char[1];
        *res.state = '\0';
        return res;
    }
    FrogState nextStateJumpRight() const
    {
        FrogState res(this->state);
        char *newState = res.state;
        while (*newState != ' ')
            ++newState;
        if (newState > res.state)
            if (newState[-1] == '>')
            {
                newState[0] = '>';
                newState[-1] = ' ';
                return res;
            }
            else if (newState > res.state + 1 &&
                     newState[-1] == '<' &&
                     newState[-2] == '>')
            {
                newState[0] = '>';
                newState[-2] = ' ';
                return res;
            }
        delete res.state;
        res.state = new char[1];
        *res.state = '\0';
        return res;
    }
};

template <typename T>
struct Box
{
    T data;
    Box *next;
    Box(const T &_data, Box *_next = nullptr)
        : data(_data), next(_next) {}
};

template <typename T>
struct stack
{
    Box<T> *top;
    stack() : top(nullptr) {}
    stack(const T &el) : top(new Box<T>(el)) {}
    stack(const stack &other) : top(nullptr)
    {
        if (!other.top)
            return;
        top = new Box<T>(other.top->data);
        Box<T> *otherIter = other.top->next;
        Box<T> *thisIter = top;
        while (otherIter)
        {
            thisIter->next = new Box<T>(otherIter->data);
            thisIter = thisIter->next;
            otherIter = otherIter->next;
        }
    }
    stack<T> &operator=(const stack<T> &other) = delete;
    ~stack()
    {
        clear();
    }
    void clear()
    {
        while (top)
            pop();
    }
    void push(const T &el)
    {
        top = new Box<T>(el, top);
    }
    T pop()
    {
        T res = top->data;
        Box<T> *tmp = top;
        top = top->next;
        delete tmp;
        return res;
    }
    T &getTop() { return top->data; }
};

bool eqStates(const FrogState &a, const FrogState &b)
{
    return !strcmp(a.state, b.state);
}

unsigned steps = 1;

void solveFrog(const FrogState &initial)
{
    stack<FrogState> st(initial);
    stack<stack<FrogState>> frames(st);
    FrogState end((strlen(initial.state) - 1) >> 1);
    FrogState buf;

    while (frames.top &&
           (!frames.getTop().top ||
            !eqStates(frames.getTop().getTop(), end)))
    {
        if (!frames.getTop().top)
        {
            frames.pop();
            if (frames.top)
                frames.getTop().pop();
            else
            {
                std::cout << "No solution!\n";
                return;
            }
            continue;
        }
        st.clear();
        buf = frames.getTop().getTop().nextStateJumpLeft();
        if (buf.validState())
            st.push(buf);
        buf = frames.getTop().getTop().nextStateJumpRight();
        if (buf.validState())
            st.push(buf);
        if (st.top)
            frames.push(st);
        else
            frames.getTop().pop();
    }
    while (frames.top)
    {
        std::cout << frames.getTop().getTop().state << '\n';
        frames.pop();
    }
}

bool less(const int &a, const int &b)
{
    return a < b;
}

void sort(Node *&head, bool (*less)(const int &, const int &))
{
    if (!head || !head->next)
        return;
    Node *iter = head->next;
    Node *prev = head;
    Node *maxEl = head->next;
    Node *maxElprev = head;
    Node *begin = head;
    Node *beginPrev = begin;
    while (begin->next)
    {
        iter = begin->next;
        prev = begin;
        maxEl = begin;
        maxElprev = beginPrev;
        while (iter)
        {
            if (less(maxEl->val, iter->val))
            {
                maxEl = iter;
                maxElprev = prev;
            }
            iter = iter->next;
            prev = prev->next;
        }
        if (maxEl == begin)
        {
            if (beginPrev == begin)
                begin = begin->next;
            else
            {
                beginPrev->next = begin->next;
                begin->next = head;
                head = begin;
                begin = beginPrev->next;
            }
        }
        else
        {
            maxElprev->next = maxEl->next;
            maxEl->next = head;
            head = maxEl;
            if (beginPrev == begin)
                beginPrev = head;
        }
    }
    begin->next = head;
    head = begin;
    beginPrev->next = nullptr;
}

int main()
{
    Node *list1 = new Node(1,
                           new Node(2,
                                    new Node(2,
                                             new Node(4,
                                                      new Node(2,
                                                               new Node(7,
                                                                        new Node(8, nullptr)))))));
    printList(list1);
    shuffle(list1);
    printList(list1);
    std::cout << "sum of list els: " << reduce(list1, plus) << '\n';
    removeAll(list1, 2);
    std::cout << "duplicates: " << std::boolalpha << duplicates(list1) << '\n';
    printList(list1);
    reverse(list1);
    printList(list1);
    clear(list1);

    Node *list2 = new Node(1,
                           new Node(2,
                                    new Node(3,
                                             new Node(1, nullptr))));

    printList(list2);
    std::cout << "is " << (palindrom(list2) ? "" : "not ")
              << "a palindrome\n";
    printList(list2);
    clear(list2);

    Node *list3 = new Node(10,
                           new Node(4,
                                    new Node(3,
                                             new Node(-2,
                                                      new Node(6,
                                                               new Node(-7,
                                                                        new Node(9,
                                                                                 new Node(1,
                                                                                          nullptr))))))));
    printList(list3);
    sort(list3, less);
    printList(list3);
    clear(list3);

    std::cout << '\n';
    solveFrog(">>> <<<");
    std::cout << '\n';

    return 0;
}