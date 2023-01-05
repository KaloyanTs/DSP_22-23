#include <iostream>

struct Node
{
    int val;
    Node *next;
    Node *prev;
    Node(int _val, Node *n = nullptr, Node *p = nullptr) : val(_val), next(n), prev(p) {}
};

void push_front(Node *&head, int el)
{
    head = new Node(el, head, nullptr);
    head->next->prev = head;
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

void clearList(Node *head)
{
    Node *tmp = head;
    while (head)
    {
        head = head->next;
        delete tmp;
        tmp = head;
    }
}

void sort(Node *&head)
{
    if (!head || !head->next)
        return;
    Node *min = head;
    Node *iter = head;
    while (iter)
    {
        if (iter->val < min->val)
            min = iter;
        iter = iter->next;
    }
    if (!min->next)
    {
        min->prev->next = nullptr;
        sort(head);
        head->prev = min;
        min->prev = nullptr;
        min->next = head;
        head = min;
        return;
    }
    if (!min->prev)
    {
        sort(head->next);
        min->next = head->next;
        head = min;
        return;
    }
    min->prev->next = min->next;
    min->next->prev = min->prev;
    sort(head);
    min->prev = nullptr;
    min->next = head;
    head = min;
}

void swapNext(Node *&p)
{
    Node *n = p->next;
    if (p->prev)
        p->prev->next = n;
    if (n->next)
        n->next->prev = p;
    p->next = n->next;
    n->prev = p->prev;
    n->next = p;
    p->prev = n;
    p = n;
}

size_t size(Node *head)
{
    size_t res = 0;
    while (head)
    {
        ++res;
        head = head->next;
    }
    return res;
}

void bubbleSort(Node *&head)
{
    if (!head || !head->next)
        return;
    Node *saveHead = head;
    Node *iter;
    size_t s = size(head);
    for (unsigned i = 0; i < s; ++i)
    {
        iter = saveHead;
        while (iter->next)
        {
            if (iter->val > iter->next->val)
            {
                if (!iter->prev)
                    saveHead = iter->next;
                swapNext(iter);
            }
            iter = iter->next;
        }
    }
    head = saveHead;
}

int main()
{
    Node *l = new Node(13);;
    push_front(l, 18);
    push_front(l, 22);
    push_front(l, 29);
    push_front(l, 0);
    push_front(l, 6);
    push_front(l, 10);
    push_front(l, 1);
    push_front(l, 2);
    push_front(l, 3);
    printList(l);
    // sort(l);
    bubbleSort(l);
    printList(l);
    clearList(l);
    return 0;
}