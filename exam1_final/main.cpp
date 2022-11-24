#include <iostream>
#include <stack>

struct Node
{
    int val;
    Node *next;
    Node(int _val, Node *_next = nullptr) : val(_val), next(_next) {}
};

void clear(Node *&head)
{
    Node *tmp = head;
    while (head)
    {
        head = head->next;
        delete tmp;
        tmp = head;
    }
    head = nullptr;
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

void insertAfter(int val, Node *head)
{
    if (!head)
        throw std::runtime_error("invalid position");
    head->next = new Node(val, head->next);
}

void longestIncOrDec(Node *head,
                     unsigned &len,
                     unsigned &sum)
{
    if (!head)
    {
        sum = 0;
        len = 0;
        return;
    }
    if (!head->next || head->next->val == head->val)
    {
        len = 1;
        sum = head->val;
        return;
    }
    len = 1;
    sum = head->val;
    bool increasing = head->val < head->next->val;
    while (head->next &&
           (increasing
                ? head->val < head->next->val
                : head->val > head->next->val))
    {
        head = head->next;
        ++len;
        sum += head->val;
    }
}

Node *copyK(Node *head, unsigned k)
{
    if (!k)
        return nullptr;
    Node *res = new Node(head->val);
    Node *resEnd = res;
    unsigned i = 0;
    while (++i < k && head->next)
    {
        head = head->next;
        insertAfter(head->val, resEnd);
        resEnd = resEnd->next;
    }
    return res;
}

Node *longestIncOrDecSublist(Node *head)
{
    if (!head)
        return nullptr;
    Node *best = head;
    unsigned bestSum;
    unsigned longest;
    unsigned thisSum;
    unsigned thisLength;
    longestIncOrDec(head, longest, bestSum);

    while (head)
    {
        longestIncOrDec(head, thisLength, thisSum);
        if (thisLength > longest ||
            (thisLength == longest && thisSum > bestSum))
        {
            best = head;
            longest = thisLength;
            bestSum = thisSum;
        }
        head = head->next;
    }
    return copyK(best, longest);
}

void removeDuplicates(Node *head)
{
    if (!head || !head->next)
        return;
    Node *iter;
    Node *iterPrev;
    while (head)
    {
        iterPrev = head;
        iter = head->next;
        while (iter)
        {
            if (iter->val == head->val)
            {
                iterPrev->next = iter->next;
                delete iter;
                iter = iterPrev->next;
            }
            else
            {
                iter = iter->next;
                iterPrev = iterPrev->next;
            }
        }
        head = head->next;
    }
}

void reverse(Node *&head)
{
    if (!head || !head->next)
        return;
    Node *prev = nullptr;
    Node *current = head;
    Node *n = head->next;
    while (n)
    {
        current->next = prev;
        prev = current;
        current = n;
        n = n->next;
    }
    current->next = prev;
    head = current;
}

void subIncHalf(Node *head)
{
    reverse(head);
    Node *slow = head, *fast = head;
    bool toInc = true;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        if (fast && fast->next)
            slow = slow->next;
    }
    fast = head;
    while (fast->val == 9)
    {
        fast->val = 0;
        if (fast == slow)
        {
            slow = slow->next = new Node(1, slow->next);
            toInc = false;
            break;
        }
        fast = fast->next;
    }
    if (toInc)
        ++fast->val;
    bool toDec = true;
    fast = slow->next;
    while (!fast->val)
    {
        fast->val = 9;
        if (!fast->next->next && fast->next->val == 1)
        {
            delete fast->next;
            fast->next = nullptr;
            toDec = false;
            break;
        }
        fast = fast->next;
        if (!fast)
            throw std::runtime_error("bad number");
    }
    if (toDec)
        --fast->val;
    reverse(head);
}

int main()
{
    Node *l = new Node(2,
                       new Node(3,
                                new Node(2,
                                         new Node(1,
                                                  new Node(0,
                                                           new Node(3,
                                                                    new Node(2, nullptr)))))));
    printList(l);

    Node *res = longestIncOrDecSublist(l);
    printList(res);

    removeDuplicates(l);
    printList(l);

    clear(l);
    clear(res);

    l = new Node(1,
                 new Node(9,
                          new Node(0,
                                   new Node(0,
                                            new Node(9,
                                                     new Node(9,
                                                              new Node(9,
                                                                       new Node(9, nullptr))))))));

    printList(l);
    subIncHalf(l);
    printList(l);

    clear(l);
    return 0;
}