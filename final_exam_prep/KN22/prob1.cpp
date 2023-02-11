#include <iostream>
#include <list>

enum Beverage
{
    BEER = 1,
    VODKA = 1 << 1,
    WHISKEY = 1 << 2,
    TEQUILLA = 1 << 3,
    COLA = 1 << 4,
    RUM = 1 << 5,
    GIN = 1 << 6,
    MINT = 1 << 7
};

struct BarSlot;
struct Client;
void takeSeat(BarSlot *s, Client *c);

struct BarSlot
{
    static const size_t SIZE = 32;
    short beverages;
    BarSlot *next;
    Client *sitting;
    BarSlot(const std::list<Beverage> &l = {}, BarSlot *_next = nullptr)
        : next(_next), sitting(nullptr), beverages(0)
    {
        for (Beverage b : l)
            beverages |= b;
    }
    bool has(Beverage b)
    {
        return beverages & b;
    }
};

struct Client
{
    short drinks;
    Client *prev, *next;
    BarSlot *seat;
    bool wants(Beverage b) const
    {
        return drinks & b;
    }
    Client(const std::list<Beverage> &l, Client *_prev = nullptr, Client *_next = nullptr)
        : drinks(0), seat(nullptr), prev(_prev), next(_next)
    {
        for (Beverage b : l)
            drinks |= b;
    }
    void print() const
    {
        if (wants(BEER))
            std::cout << "BEER\t";
        if (wants(VODKA))
            std::cout << "VODKA\t";
        if (wants(WHISKEY))
            std::cout << "WHISKEY\t";
        if (wants(TEQUILLA))
            std::cout << "TEQUILLA\t";
        if (wants(COLA))
            std::cout << "COLA\t";
        if (wants(RUM))
            std::cout << "RUM\t";
        if (wants(GIN))
            std::cout << "GIN\t";
        if (wants(MINT))
            std::cout << "MINT\t";
    }
    bool canSit(BarSlot *s)
    {
        return !s->sitting && !(drinks & (~s->beverages));
    }
    bool sit(BarSlot *s)
    {
        if (!canSit(s))
            return false;
        s->sitting = this;
        seat = s;
        return true;
    }
    bool stand()
    {
        if (!seat)
            return false;
        seat->sitting = nullptr;
        seat = nullptr;
        return true;
    }
};

void print(BarSlot *b)
{
    std::cout << "seat has:\n\t";
    if (b->has(BEER))
        std::cout << "BEER\t";
    if (b->has(VODKA))
        std::cout << "VODKA\t";
    if (b->has(WHISKEY))
        std::cout << "WHISKEY\t";
    if (b->has(TEQUILLA))
        std::cout << "TEQUILLA\t";
    if (b->has(COLA))
        std::cout << "COLA\t";
    if (b->has(RUM))
        std::cout << "RUM\t";
    if (b->has(GIN))
        std::cout << "GIN\t";
    if (b->has(MINT))
        std::cout << "MINT\t";
    std::cout << "\n\ttaken by:\n\t";
    if (b->sitting)
        b->sitting->print();
    else
        std::cout << '-';
    std::cout << '\n';
}

template <typename List>
void clear(List *&b)
{
    List *tmp = b;
    while (b)
    {
        b = b->next;
        delete tmp;
        tmp = b;
    }
}

bool place(BarSlot *bar, Client *clients, unsigned dist = 0)
{

    if (!clients)
        return true;
    if (!bar)
        return false;
    if (dist > 5 && clients->prev)
        return false;
    if (clients->sit(bar))
    {
        if (place(bar->next, clients->next, 1))
            return true;
        clients->stand();
        return place(bar->next, clients, 0);
    }
    return place(bar->next, clients, dist + 1);

    // if (!bar)
    //     return false;
    // unsigned counter{0};
    // BarSlot *lastTaken = nullptr;
    // while (clients)
    // {
    //     counter = 0;
    //     while (!clients->sit(bar))
    //     {
    //         bar = bar->next;
    //         if (lastTaken)
    //             ++counter;
    //         if (counter > 5)
    //         {
    //             while (clients->prev)
    //             {
    //                 clients->prev->stand();
    //                 clients = clients->prev;
    //             }
    //             return place(lastTaken->next, clients);
    //         }
    //     }
    //     if (!lastTaken)
    //         lastTaken = bar;
    //     clients = clients->next;
    //     bar = bar->next;
    //     if (!bar)
    //         return !clients;
    // }

    // return true;
}

void printBar(BarSlot *head)
{
    while (head)
    {
        print(head);
        head = head->next;
    }
}

Client *makeGroup(const std::list<std::list<Beverage>> &l)
{
    if (l.empty())
        return nullptr;
    std::list<std::list<Beverage>>::const_iterator i = l.begin();
    Client *head = new Client(*i++);
    Client *tail = head;
    while (i != l.cend())
        tail = tail->next = new Client(*i++, tail);
    return head;
}

BarSlot *makeBar(const std::list<std::list<Beverage>> &l)
{
    if (l.empty())
        return nullptr;
    std::list<std::list<Beverage>>::const_iterator i = l.begin();
    BarSlot *head = new BarSlot(*i++);
    BarSlot *tail = head;
    while (i != l.cend())
        tail = tail->next = new BarSlot(*i++);
    return head;
}

bool placeAll(BarSlot *bar, Client **groups, int groupCount)
{
    if (!groupCount)
        return true;
    if (!bar)
        return false;
    while (bar)
        if (place(bar, groups[0]) && placeAll(bar, &groups[1], groupCount - 1))
            return true;
        else
            bar = bar->next;
    return false;
}

int main()
{
    Client *arr[2];
    arr[0] = makeGroup({{BEER, GIN}, {VODKA, WHISKEY, BEER}, {RUM, TEQUILLA, WHISKEY}});
    arr[1] = makeGroup({{BEER}, {RUM, COLA, GIN}});
    BarSlot *b = makeBar({{BEER},
                          {BEER},
                          {RUM, GIN, VODKA, WHISKEY, BEER},
                          {RUM, TEQUILLA, WHISKEY},
                          {VODKA, BEER, TEQUILLA, WHISKEY},
                          {RUM, COLA, WHISKEY},
                          {RUM, COLA, GIN},
                          {RUM, COLA, WHISKEY},
                          {RUM, TEQUILLA, WHISKEY},
                          {RUM, COLA, WHISKEY},
                          {RUM, GIN, MINT},
                          {COLA, TEQUILLA, WHISKEY}});
    printBar(b);
    // std::cout << std::boolalpha << place(b, arr[0]) << '\n';
    std::cout << std::boolalpha << placeAll(b, arr, 2) << '\n';
    printBar(b);

    clear(arr[0]);
    clear(arr[1]);
    clear(b);
    return 0;
}