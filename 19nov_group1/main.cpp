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

void nextStateJumpLeft(const char *state, char *&newState)
{
    newState = new char(strlen(state) + 1);
    strcpy(newState, state);
    char *begin = newState;
    while (*newState != ' ')
        ++newState;
    if (newState[1])
        if (newState[1] == 'r')
        {
            newState[0] = 'r';
            newState[1] = ' ';
            newState = begin;
            return;
        }
        else if (newState[2] && newState[1] == 'l' && newState[2] == 'r')
        {
            newState[0] = 'r';
            newState[2] = ' ';
            newState = begin;
            return;
        }
    delete newState;
    newState = nullptr;
}

struct FrogNode
{
    char *state;
    FrogNode *next;
    FrogNode(const char *_state, FrogNode *_next)
        : state(new char(strlen(_state) + 1)), next(_next)
    {
        strcpy(state, _state);
    }
    ~FrogNode()
    {
        delete state;
    }
    bool validState() const { return state; }
};

void solveFrog(FrogNode *initial)
{
    
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
                                    new Node(2,
                                             new Node(1, nullptr))));

    printList(list2);
    std::cout << "is " << (palindrom(list2) ? "" : " not ")
              << "a palindrome\n";
    printList(list2);
    clear(list2);

    return 0;
}