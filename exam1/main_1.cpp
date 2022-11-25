#include <iostream>

template <typename T>
struct Node
{
    T value;
    Node<T> *next;
};

template <typename T>
void printList(Node<T> *head)
{
    while (head)
    {
        std::cout << head->value << ' ';
        head = head->next;
    }
    std::cout << '\n';
}

template <typename T>
void clear(Node<T> *&head)
{
    Node<T> *tmp = head;
    while (head)
    {
        head = head->next;
        delete tmp;
        tmp = head;
    }
    head = nullptr;
}

template <typename T>
void rotateOnce(Node<T> *&head, Node<unsigned> *interval)
{
    if (interval->value == interval->next->value)
        return;
    if (interval->value > interval->next->value)
        throw std::logic_error("bad index");
    unsigned start = 0;
    Node<T> *from = head;
    Node<T> *fromPrev = nullptr;
    Node<T> *toPrev = nullptr;
    while (start < interval->value)
    {
        if (start == interval->value - 1)
            fromPrev = from;
        from = from->next;
        if (!from)
            throw std::logic_error("bad index");
        ++start;
    }
    Node<T> *to = from;
    while (start < interval->next->value)
    {
        if (start == interval->next->value - 1)
            toPrev = to;
        to = to->next;
        if (!to)
            throw std::logic_error("bad index");
        ++start;
    }
    if (!fromPrev)
    {
        toPrev->next = to->next;
        to->next = head;
        head = to;
        return;
    }
    toPrev->next = to->next;
    to->next = from;
    fromPrev->next = to;
}

template <typename T>
void rotateSublists(Node<T> *&list, Node<Node<unsigned> *> *intervals)
{
    while (intervals)
    {
        rotateOnce(list, intervals->value);
        intervals = intervals->next;
    }
}

int main()
{
    Node<int> *l = new Node<int>{11,
                                 new Node<int>{4,
                                               new Node<int>{3,
                                                             new Node<int>{7,
                                                                           new Node<int>{13,
                                                                                         new Node<int>{4,
                                                                                                       new Node<int>{5, nullptr}}}}}}};
    Node<unsigned> *interval1 = new Node<unsigned>{1, new Node<unsigned>{3, nullptr}};
    Node<unsigned> *interval2 = new Node<unsigned>{2, new Node<unsigned>{5, nullptr}};
    Node<unsigned> *interval3 = new Node<unsigned>{5, new Node<unsigned>{6, nullptr}};

    Node<Node<unsigned> *> intervals3{interval3, nullptr};
    Node<Node<unsigned> *> intervals2{interval2, &intervals3};
    Node<Node<unsigned> *> intervals{interval1, &intervals2};

    printList(l);
    rotateSublists(l, &intervals);
    std::cout << "Rotated into: ";
    printList(l);

    clear(l);
    clear(interval1);
    clear(interval2);
    clear(interval3);
    return 0;
}