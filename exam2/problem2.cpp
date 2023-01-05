#include <iostream>

template <typename T>
struct DLListElem
{
    T data;
    DLListElem<T> *next, *prev;
    DLListElem<T>(const T &d, DLListElem<T> *n = nullptr, DLListElem<T> *p = nullptr) : data(d), next(n), prev(p) {}
};

template <typename T>
void clear(DLListElem<T> *&head, DLListElem<T> *&end)
{
    DLListElem<T> *tmp = head;
    while (head)
    {
        head = head->next;
        delete tmp;
        tmp = head;
    }
    end = nullptr;
}

template <typename T>
void print(DLListElem<T> *head)
{
    while (head)
    {
        std::cout << head->data << ' ';
        head = head->next;
    }
    std::cout << '\n';
}

template <typename T>
void push_back(DLListElem<int> *&begin, DLListElem<int> *&end, const T &val)
{
    if (!begin)
    {
        begin = end = new DLListElem<T>(val);
        return;
    }
    end->next = new DLListElem<T>(val, nullptr, end);
    end = end->next;
}

template <typename T>
void makeSwap(DLListElem<T> *&ptr)
{
    DLListElem<T> *ptrNext = ptr->next;
    if (ptr->prev)
        ptr->prev->next = ptrNext;
    if (ptrNext->next)
        ptrNext->next->prev = ptr;
    ptr->next = ptrNext->next;
    ptrNext->prev = ptr->prev;
    ptr->prev = ptrNext;
    ptrNext->next = ptr;
    ptr = ptrNext;
}

// O(n^2) - bubble sort
template <typename T>
void sortDescending(DLListElem<T> *&start, DLListElem<T> *&end)
{
    if (!start || start == end)
        return;
    DLListElem<T> *iterTo = end, *iter = end;
    while (iterTo != start)
    {
        iter = start;
        while (iter != iterTo)
        {
            if (iter->data < iter->next->data)
            {
                if (iter == start)
                    start = iter->next;
                if (iter->next == end)
                    end = iter;
                if (iter->next == iterTo)
                    iterTo = iter;
                makeSwap(iter);
            }
            iter = iter->next;
        }
        iterTo = iterTo->prev;
    }
}

int main()
{
    DLListElem<int> *head = nullptr, *end = nullptr;
    push_back(head, end, 5);
    push_back(head, end, 7);
    push_back(head, end, 2);
    push_back(head, end, 6);
    push_back(head, end, 1);
    push_back(head, end, 4);
    push_back(head, end, 3);

    std::cout << "Original list:\t";
    print(head);
    sortDescending(head, end);
    std::cout << "Sorted list:\t";
    print(head);

    clear(head, end);

    push_back(head, end, 0);
    push_back(head, end, 7);
    push_back(head, end, -3);
    push_back(head, end, 10);
    push_back(head, end, 1);
    push_back(head, end, -2);
    push_back(head, end, 3);

    std::cout << "Original list:\t";
    print(head);
    sortDescending(head, end);
    std::cout << "Sorted list:\t";
    print(head);

    clear(head, end);

    return 0;
}