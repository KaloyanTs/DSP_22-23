#include <iostream>

struct Node
{
    int val;
    Node *next;
    Node(int _val, Node *_next = nullptr) : val(_val), next(_next) {}
};

void printList(Node *head)
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
    head = nullptr;
}

void reverse(Node *&head)
{
    if (!head || !head->next)
        return;
    Node *prev = nullptr;
    Node *headNext = head->next;
    while (headNext)
    {
        head->next = prev;
        prev = head;
        head = headNext;
        headNext = headNext->next;
    }
    head->next = prev;
}

void reverseEachK(Node *&head, unsigned k)
{
    if (k == 1)
        return;
    Node *groupEnd = head;
    Node *nextGroup;
    Node *newHead;
    Node *lastGroupEnd = nullptr;
    unsigned c = 0;
    bool first = false;
    while (groupEnd)
    {
        c = 0;
        while (groupEnd && ++c < k)
            groupEnd = groupEnd->next;
        if (!groupEnd)
            break;
        if (!first)
        {
            first = true;
            newHead = groupEnd;
        }
        if (lastGroupEnd)
            lastGroupEnd->next = groupEnd;
        lastGroupEnd = head;
        nextGroup = groupEnd->next;
        groupEnd->next = nullptr;
        groupEnd = head;
        reverse(head);
        groupEnd->next = nextGroup;
        head = groupEnd = nextGroup;
        lastGroupEnd->next = head;
    }
    head = newHead;
}

struct SumNode
{
    int val;
    SumNode *next;
    Node *assoc;
    SumNode(int _val, Node *_assoc, SumNode *_next = nullptr)
        : val(_val), next(_next), assoc(_assoc) {}
};

void printListSum(SumNode *head)
{
    while (head)
    {
        if (head->assoc)
            std::cout << head->assoc->val
                      << '(' << head->val << ')' << '\n';
        else
            std::cout << 'x'
                      << '(' << head->val << ')' << '\n';

        head = head->next;
    }
    std::cout << '\n';
}

bool removeZeroSum(Node *&head)
{
    Node *iter = head;
    SumNode *sumsHead = new SumNode(0, head);
    SumNode *sumIter = sumsHead;
    SumNode *sumIterPrev = nullptr;
    SumNode *seeker;
    int allSum = 0;
    while (iter)
    {
        allSum += iter->val;
        iter = iter->next;
        sumIter->next = new SumNode(allSum, iter);
        sumIter = sumIter->next;
    }
    sumIter = sumsHead;
    while (sumIter->next)
    {
        seeker = sumIter->next;
        while (seeker)
        {
            if (seeker->val == sumIter->val)
            {
                if (sumIterPrev)
                {
                    sumIterPrev->assoc->next = seeker->assoc;
                    SumNode *tmp = sumIter;
                    while (sumIter != seeker)
                    {
                        sumIter = sumIter->next;
                        delete tmp->assoc;
                        tmp = sumIter;
                    }
                }
                else
                {
                    head = seeker->assoc;
                    SumNode *tmp = sumIter;
                    while (sumIter != seeker)
                    {
                        sumIter = sumIter->next;
                        delete tmp->assoc;
                        tmp = sumIter;
                    }
                }
                SumNode *clean = sumsHead;
                while (sumsHead)
                {
                    sumsHead = sumsHead->next;
                    delete clean;
                    clean = sumsHead;
                }
                return true;
            }
            seeker = seeker->next;
        }
        if (sumIterPrev)
            sumIterPrev = sumIterPrev->next;
        else
            sumIterPrev = sumIter;
        sumIter = sumIter->next;
    }
    SumNode *clean = sumsHead;
    while (sumsHead)
    {
        sumsHead = sumsHead->next;
        delete clean;
        clean = sumsHead;
    }
    return false;
}

void removeAllZeroSums(Node *&head)
{
    while (removeZeroSum(head))
    {
    }
}

void mergeLists(Node *&l1, Node *&l2)
{
    if (!l2)
        return;
    if (!l1)
    {
        l1 = l2;
        l2 = nullptr;
        return;
    }
    Node *l1Iter = l1, *l1IterNext = l1->next;
    Node *l2Iter = l2, *l2IterNext = l2->next;

    while (l1IterNext && l2IterNext)
    {
        l1Iter->next = l2Iter;
        l2Iter->next = l1IterNext;
        l1Iter = l1IterNext;
        l2Iter = l2IterNext;
        l1IterNext = l1IterNext->next;
        l2IterNext = l2IterNext->next;
    }
    if (!l2IterNext)
        l2Iter->next = l1Iter->next;
    l1Iter->next = l2Iter;

    l2 = nullptr;
}

void reorderList(Node *&head)
{
    Node *fast = head;
    Node *slow = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        if (fast && fast->next)
            slow = slow->next;
    }
    Node *head2 = slow->next;
    slow->next = nullptr;
    reverse(head2);
    mergeLists(head, head2);
}

void insertIntoCyclic(Node *head, int insertVal)
{
    Node *iter = head;
    while (!(iter->val <= insertVal &&
             iter->next->val > insertVal) &&
           !((iter->val > iter->next->val) &&
             (insertVal <= iter->next->val)))
        iter = iter->next;
    iter->next = new Node(insertVal, iter->next);
}

void printCycleList(Node *cycle)
{
    Node *iter = cycle->next;
    std::cout << cycle->val << ' ';
    while (iter != cycle)
    {
        std::cout << iter->val << ' ';
        iter = iter->next;
    }
    std::cout << '\n';
}

void clearCycleList(Node *head)
{
    Node *from = head->next;
    head->next = nullptr;
    head = from;
    clear(head);
}

void oddEvenLinkedList(Node *list)
{
    if (!list || !list->next || !list->next->next)
        return;
    Node *evens = list->next;
    Node *oddIter = list;
    Node *evenIter = list->next;

    while (evenIter && oddIter)
    {
        oddIter->next = evenIter->next;
        if (!oddIter->next)
            break;
        oddIter = oddIter->next;
        evenIter->next = oddIter->next;
        evenIter = evenIter->next;
    }
    if (evenIter)
        evenIter->next = nullptr;
    oddIter->next = evens;
}

int main()
{
    Node *l1 = new Node(1,
                        new Node(2,
                                 new Node(3,
                                          new Node(4,
                                                   new Node(5, nullptr)))));

    printList(l1);
    reverseEachK(l1, 2);
    printList(l1);
    reverse(l1);
    printList(l1);
    clear(l1);

    Node *l2 = new Node(1,
                        new Node(2,
                                 new Node(3,
                                          new Node(-3,
                                                   new Node(-2, nullptr)))));

    printList(l2);
    removeAllZeroSums(l2);
    printList(l2);
    clear(l2);

    Node *l3 = new Node(1,
                        new Node(2,
                                 new Node(3,
                                          new Node(4,
                                                   new Node(5, nullptr)))));
    printList(l3);
    reorderList(l3);
    printList(l3);
    clear(l3);

    Node *cycle = new Node(3, nullptr);
    cycle->next = new Node(4, new Node(1, cycle));
    printCycleList(cycle);
    insertIntoCyclic(cycle, 2);
    printCycleList(cycle);
    clearCycleList(cycle);

    Node *l5 = new Node(1,
                        new Node(2,
                                 new Node(3,
                                          new Node(4,
                                                   new Node(5, nullptr)))));
    printList(l5);
    oddEvenLinkedList(l5);
    printList(l5);
    clear(l5);

    return 0;
}