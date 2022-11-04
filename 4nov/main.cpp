#include <iostream>
#include <list>

template <typename T>
struct ListEl
{
    T data;
    ListEl *next;
    ListEl(const T &_data) : data(_data), next(nullptr) {}
    ListEl(unsigned n, const T d[])
    {
        ListEl *temp = this;
        this->data = d[0];
        for (unsigned i = 1; i < n; ++i)
        {
            temp->next = new ListEl(d[i]);
            temp = temp->next;
        }
    }
};

template <typename T>
void printList(const ListEl<T> *head)
{
    while (head)
    {
        std::cout << head->data << ' ';
        head = head->next;
    }
    std::cout << '\n';
}

template <typename T>
void erase(ListEl<T> *head)
{
    ListEl<T> *temp = head;
    while (head)
    {
        head = head->next;
        delete temp;
        temp = head;
    }
}

template <typename T>
void reverse(ListEl<T> *&head)
{
    if (!head->next)
        return;
    ListEl<T> *n = head->next;
    ListEl<T> *p = nullptr;

    while (n)
    {
        head->next = p;
        p = head;
        head = n;
        n = n->next;
    }
    head->next = p;
}

template <typename T>
void removeSuccDuplicates(ListEl<T> *head)
{
    ListEl<T> *tail = head;
    while (tail->next)
    {
        if (tail->data == tail->next->data)
        {
            ListEl<T> *temp = tail->next;
            tail->next = temp->next;
            delete temp;
        }

        tail = tail->next;
    }
}

template <typename T>
void removeDuplicates(ListEl<T> *head)
{
    ListEl<T> *temp, *tempPrev;
    while (head)
    {
        temp = head->next;
        tempPrev = head;
        while (temp)
        {
            if (temp->data == head->data)
            {
                tempPrev->next = temp->next;
                delete temp;
            }
            else
                tempPrev = tempPrev->next;
            temp = tempPrev->next;
        }
        head = head->next;
    }
}

template <typename T>
void append(ListEl<T> *l1, ListEl<T> *l2)
{
    if (!l2)
        return;
    if (!l1)
    {
        l1 = new ListEl<T>(l2->data);
        l2 = l2->next;
    }
    while (l1->next)
        l1 = l1->next;
    while (l2)
    {
        l1->next = new ListEl<T>(l2->data);
        l2 = l2->next;
        l1 = l1->next;
    }
}

template <typename T>
void divide(ListEl<T> *&head, bool (*p)(const T &el))
{
    ListEl<T> *t = nullptr, *f = nullptr;
    ListEl<T> *tBegin = t, *fBegin = f;
    while (head)
        if (p(head->data))
        {
            if (!tBegin)
            {
                tBegin = head;
                t = tBegin;
                head = head->next;
            }
            else
            {
                t->next = head;
                head = head->next;
                t = t->next;
            }
            t->next = nullptr;
        }
        else
        {
            if (!fBegin)
            {
                fBegin = head;
                f = fBegin;
                head = head->next;
            }
            else
            {
                f->next = head;
                head = head->next;
                f = f->next;
            }
            f->next = nullptr;
        }
    append(tBegin, fBegin);
    head = tBegin;
}

bool isEven(const int &x) { return x % 2 == 0; }

int main()
{
    int elem[] = {1, 1, 1, 3, 4, 5, 5, 2, 3, 7};
    ListEl<int> *head = new ListEl<int>{
        sizeof(elem) / sizeof(elem[0]),
        elem};
    printList(head);
    reverse(head);
    printList(head);

    removeSuccDuplicates(head);
    printList(head);
    erase(head);

    int elem2[] = {1, 2, 1, 4, 5, 3, 1, 2, 9, 2};
    head = new ListEl<int>{
        sizeof(elem2) / sizeof(elem2[0]),
        elem2};

    printList(head);
    removeDuplicates(head);
    printList(head);
    erase(head);

    ListEl<int> *l1 = new ListEl<int>{
                    sizeof(elem) / sizeof(elem[0]),
                    elem},
                *l2 = new ListEl<int>{sizeof(elem2) / sizeof(elem2[0]), elem2};

    append(l1, l2);
    printList(l1);

    divide(l2, isEven);
    printList(l2);
    erase(l1);
    erase(l2);

    return 0;
}