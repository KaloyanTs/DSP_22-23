#include <iostream>
#include <cmath>

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
bool isFullyConsecutive(Node<T> *head)
{
    if (!head || !head->next)
        return false;
    Node<T> *n = head->next;
    while (n && abs(n->value - head->value) == 1)
    {
        head = head->next;
        n = n->next;
    }
    return !n;
}

bool makeTotal(Node<int> *&head)
{
    if (isFullyConsecutive(head))
        return true;
    if (!head || !head->next)
        return false;
    Node<int> *saveHead = head;
    Node<int> *iter = head->next;
    while (iter)
    {
        while (iter && abs(iter->value - head->value) == 1)
        {
            head->next = iter->next;
            delete iter;
            iter = head->next;
        }
        if (!iter)
            return false;
        head = head->next;
        iter = iter->next;
    }
    head = saveHead;
    return false;
}

int main()
{
    Node<int> *l = new Node<int>{2,
                                 new Node<int>{1,
                                               new Node<int>{2,
                                                             new Node<int>{3,
                                                                           new Node<int>{4,
                                                                                         new Node<int>{3, nullptr}}}}}};
    printList(l);
    std::cout << "The list is ";
    if (!makeTotal(l))
        std::cout << "now fully in";
    else
        std::cout << "fully ";
    std::cout << "consecutive.\nTransformed list: ";
    printList(l);
    clear(l);
    std::cout << '\n';

    l = new Node<int>{1, new Node<int>{2,
                                       new Node<int>{2,
                                                     new Node<int>{3,
                                                                   new Node<int>{4,
                                                                                 new Node<int>{2,
                                                                                               new Node<int>{5, nullptr}}}}}}};
    printList(l);
    std::cout << "The list is ";
    if (!makeTotal(l))
        std::cout << "now fully in";
    else
        std::cout << "fully ";
    std::cout << "consecutive.\nTransformed list: ";
    printList(l);
    clear(l);

    return 0;
}