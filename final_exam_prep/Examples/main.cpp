#include <iostream>

struct Node
{
    int val;
    Node *next;
    Node(int _val, Node *_next = nullptr) : val(_val), next(_next) {}
};

void print(Node *head)
{
    while (head)
    {
        std::cout << head->val << ' ';
        head = head->next;
    }
    std::cout << '\n';
}

void clear(Node *&head)
{
    Node *tmp = head;
    while (head)
    {
        head = head->next;
        delete tmp;
        tmp = head;
    }
}

void merge(Node *&l1, Node *&l2)
{
    if (!l1)
    {
        l1 = l2;
        l2 = nullptr;
        return;
    }
    if (!l2)
        return;
    Node *i1 = l1, *i2 = l2;
    Node *t = (l1->val < l2->val ? l1 : l2);
    l1 = t;
    l2 = nullptr;
    if (i1->val < i2->val)
        i1 = i1->next;
    else
        i2 = i2->next;
    while (i1 && i2)
    {
        if (i1->val < i2->val)
        {
            t = t->next = i1;
            i1 = i1->next;
        }
        else
        {
            t = t->next = i2;
            i2 = i2->next;
        }
    }
    while (i1)
    {
        t = t->next = i1->next;
        i1 = i1->next;
    }
    while (i2)
    {
        t = t->next = i2->next;
        i2 = i2->next;
    }
}

int main()
{
    Node *l1 = new Node(4, new Node(7, new Node(10, new Node(13, new Node(14, new Node(15))))));
    Node *l2 = new Node(1, new Node(2, new Node(6, new Node(12, new Node(15, new Node(16))))));

    print(l1);
    print(l2);

    merge(l1, l2);

    print(l1);
    print(l2);

    clear(l1);
    clear(l2);
    return 0;
}