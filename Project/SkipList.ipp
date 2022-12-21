template <typename T>
std::ostream &operator<<(std::ostream &os, const SkipList<T> &s)
{
    typename SkipList<T>::Node *iter = s.begin;
    while (iter)
    {
        iter->print(os);
        std::cout << '\n';
        iter = iter->next;
    }
    return os;
}

template <typename T>
typename SkipList<T>::Node *SkipList<T>::find(const T &data) const
{
    SkipList<T>::Node *i = begin;
    while (i && i->data != data)
        i = i->next;
    return i;
}

template <typename T>
void SkipList<T>::Node::print(std::ostream &os) const
{
    os << data;
    if (skip)
        os << "(link to " << skip->data << ')';
}

template <typename T>
void SkipList<T>::copy(const SkipList &other)
{
    Node *otherIter = other.begin;
    while (otherIter)
    {
        push_back(otherIter->data);
        otherIter = otherIter->next;
    }
    otherIter = other.begin;
    Node *thisIter = begin;
    while (otherIter)
    {
        if (otherIter->skip)
            thisIter->skip = find(otherIter->skip->data);
        otherIter = otherIter->next;
        thisIter = thisIter->next;
    }
}

template <typename T>
void SkipList<T>::clear()
{
    end = begin;
    while (begin)
    {
        begin = begin->next;
        delete end;
        end = begin;
    }
    begin = end = nullptr;
}

template <typename T>
SkipList<T>::SkipList()
    : begin(nullptr), end(nullptr)
{
}

template <typename T>
SkipList<T>::SkipList(const T &data)
    : begin(new SkipList::Node(data)), end(begin)
{
}

template <typename T>
SkipList<T>::SkipList(const SkipList &other)
    : begin(nullptr), end(nullptr)
{
    copy(other);
}

template <typename T>
SkipList<T> &SkipList<T>::operator=(const SkipList &other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }
}

template <typename T>
SkipList<T>::~SkipList()
{
    clear();
}

template <typename T>
SkipList<T> &SkipList<T>::push_back(const T &data)
{
    end = end->next = new SkipList<T>::Node(data);
    return *this;
}

template <typename T>
SkipList<T> &SkipList<T>::addLink(const T &from, const T &to)
{
    Node *f = find(from);
    if (!f)
        throw std::runtime_error("Cannot add link from non-existent element!");
    Node *t = find(to);
    if (!t)
        throw std::runtime_error("Cannot add link to non-existent element!");
    f->skip = t;
    return *this;
}