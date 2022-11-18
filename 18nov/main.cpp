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

void mergeSortedLists(Node *&head1, Node *&head2)
{
    Node *resTail = nullptr, *resHead = nullptr;
    while (head1 && head2)
    {
        if (head1->val < head2->val)
        {
            if (!resHead)
                resHead = head1;
            if (!resTail)
                resTail = head1;
            else
            {
                resTail->next = head1;
                resTail = resTail->next;
            }
            head1 = head1->next;
        }
        else
        {
            if (!resHead)
                resHead = head2;
            if (!resTail)
                resTail = head2;
            else
            {
                resTail->next = head2;
                resTail = resTail->next;
            }
            head2 = head2->next;
        }
    }
    while (head1)
    {
        resTail->next = head1;
        head1 = head1->next;
    }
    while (head2)
    {
        resTail->next = head2;
        head2 = head2->next;
    }
    head1 = resHead;
    head2 = nullptr;
}

int middleElement(Node *l)
{
    if (!l->next)
        return l->val;
    Node *tmp = l;
    while (tmp && tmp->next)
    {
        tmp = tmp->next->next;
        if (tmp)
            l = l->next;
    }
    return l->val;
}

void clear(Node *l)
{
    Node *tmp = l;
    while (l)
    {
        l = l->next;
        delete tmp;
    }
}

void insertAfter(int x, Node *pos)
{
    pos->next = new Node(x, pos->next);
}

void mirrorList(Node *list)
{
    if (!list)
        return;
    Node *last = list;
    while (last->next)
        last = last->next;
    while (list != last)
    {
        insertAfter(list->val, last);
        list = list->next;
    }
    insertAfter(list->val, last);
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
    Node *list2 = new Node(-4,
                           new Node(-3,
                                    new Node(-1,
                                             new Node(0,
                                                      new Node(0,
                                                               new Node(5,
                                                                        new Node(7,
                                                                                 new Node(10,
                                                                                          new Node(17,
                                                                                                   new Node(31, nullptr))))))))));
    printList(list1);
    printList(list2);
    mergeSortedLists(list1, list2);
    printList(list1);
    printList(list2);

    Node *list3 = new Node(-4,
                           new Node(-3,
                                    new Node(-1,
                                             new Node(0,
                                                      new Node(0, nullptr)))));

    printList(list3);
    std::cout << middleElement(list3) << '\n';

    mirrorList(list1);
    printList(list1);

    clear(list1);
    clear(list2);
    clear(list3);

    return 0;
}