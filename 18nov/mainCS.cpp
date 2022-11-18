#include <iostream>

struct Node
{
    int val;
    Node *next;
    Node(int _val, Node *_next) : val(_val), next(_next) {}
};

void printList(Node *l)
{
    while (l)
    {
        std::cout << l->val << ' ';
        l = l->next;
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

void insertAfter(int val, Node *pos)
{
    pos->next = new Node(val, pos->next);
}

void fillgaps(Node *head)
{
    if (!head || !head->next)
        return;

    int i = head->val + 1;
    while (head->next)
    {
        while (i < head->next->val)
        {
            insertAfter(i, head);
            head = head->next;
            ++i;
        }
        head = head->next;
        ++i;
    }
}

int main()
{
    Node *list1 = new Node(2,
                           new Node(2,
                                    new Node(4,
                                             new Node(7,
                                                      new Node(11,
                                                               new Node(12,
                                                                        new Node(17,
                                                                                 new Node(21, nullptr))))))));
    printList(list1);
    fillgaps(list1);
    printList(list1);
    return 0;
}