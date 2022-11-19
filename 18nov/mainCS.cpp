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

void removeldx(Node *head)
{
    Node *headPrev = head;
    Node *last = head;
    unsigned lastIndex = 0, currentIndex = 0;
    while (last->next)
    {
        last = last->next;
        ++lastIndex;
    }
    while (head)
    {
        if (head->val == (lastIndex - currentIndex))
        {
            if (headPrev == head)
            {
                head = head->next;
                delete headPrev;
            }
            else
            {
                headPrev->next = head->next;
                delete head;
                head = headPrev->next;
            }
        }
        else
        {
            if (headPrev != head)
                headPrev = headPrev->next;
            head = head->next;
        }
        ++currentIndex;
    }
}

bool existsInSecond(Node *l1, unsigned size, Node *l2)
{
    unsigned i = 0;
    Node *iter1 = l1, *iter2 = l2;
    while (true)
    {
        while (l2 && l2->val != l1->val)
        {
            l2 = l2->next;
        }
        if (!l2)
            return false;
        iter1 = l1;
        iter2 = l2;
        i = 0;
        while (i < size && iter2 && iter1->val == iter2->val)
        {
            if (!iter1)
                return false;
            iter1 = iter1->next;
            iter2 = iter2->next;
            ++i;
        }
        if (!iter2)
            return false;
        if (i == size)
            return true;
        l2 = l2->next;
    }
    return false;
}

bool dupsub(Node *l1, Node *l2, unsigned k)
{
    while (l1 && !existsInSecond(l1, k, l2))
        l1 = l1->next;
    return l1;
}

void removedups(Node *head)
{
    Node *headPrev = head;
    head = head->next;
    while (head)
    {
        if (head->val == headPrev->val)
        {
            headPrev->next = head->next;
            delete head;
            head = headPrev->next;
        }
        else
        {
            head = head->next;
            headPrev = headPrev->next;
        }
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
    clear(list1);

    Node *list2 = new Node(2,
                           new Node(6,
                                    new Node(4,
                                             new Node(7,
                                                      new Node(11,
                                                               new Node(2,
                                                                        new Node(17,
                                                                                 new Node(21, nullptr))))))));

    printList(list2);
    removeldx(list2);
    printList(list2);
    clear(list2);

    Node *list3 = new Node(1,
                           new Node(2,
                                    new Node(3,
                                             new Node(4,
                                                      new Node(1,
                                                               new Node(2,
                                                                        new Node(5, nullptr)))))));

    Node *list4 = new Node(1,
                           new Node(2,
                                    new Node(6,
                                             new Node(3,
                                                      new Node(3,
                                                               new Node(4, nullptr))))));

    std::cout << dupsub(list3, list4, 3) << '\n';
    clear(list3);
    clear(list4);

    Node *list5 = new Node(1,
                           new Node(1,
                                    new Node(2,
                                             new Node(3,
                                                      new Node(3,
                                                               new Node(3, nullptr))))));

    printList(list5);
    removedups(list5);
    printList(list5);
    clear(list5);

    return 0;
}