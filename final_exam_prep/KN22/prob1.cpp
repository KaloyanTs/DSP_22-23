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

struct BarSlot
{
    static const size_t SIZE = 32;
    short beverages;
    BarSlot *next;
    BarSlot(const std::list<Beverage> &l = {}, BarSlot *_next = nullptr)
        : next(_next)
    {
        for (Beverage b : l)
            beverages |= b;
    }
};

struct Client
{
    short drinks;
    Client *next;
    bool wants(Beverage b) const
    {
        return drinks & b;
    }
    Client(const std::list<Beverage> &l)
        : drinks(0)
    {
        for (Beverage b : l)
            drinks |= b;
    }
    void print() const
    {
        if (wants(BEER))
            std::cout << "BEER\n";
        if (wants(VODKA))
            std::cout << "VODKA\n";
        if (wants(WHISKEY))
            std::cout << "WHISKEY\n";
        if (wants(TEQUILLA))
            std::cout << "TEQUILLA\n";
        if (wants(COLA))
            std::cout << "COLA\n";
        if (wants(RUM))
            std::cout << "RUM\n";
        if (wants(GIN))
            std::cout << "GIN\n";
        if (wants(MINT))
            std::cout << "MINT\n";
    }
    bool canSit(BarSlot *seat)
    {
        return !(drinks & (~seat->beverages));
    }
};

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

bool place(BarSlot *bar, Client *clients)
{
    return true;
}

Client *makeGroup(const std::list<std::list<Beverage>> &l)
{
    if (l.empty())
        return nullptr;
    std::list<std::list<Beverage>>::const_iterator i = l.begin();
    Client *head = new Client(*i++);
    Client *tail = head;
    while (i != l.cend())
        tail = tail->next = new Client(*i++);
    return head;
}

int main()
{
    Client *l = makeGroup({{BEER, GIN}, {VODKA, WHISKEY, BEER}, {RUM, TEQUILLA, WHISKEY}});
    Client *i = l;
    while (i)
    {
        std::cout << '-';
        i->print();
        i = i->next;
    }
    BarSlot *b = new BarSlot({BEER, VODKA, WHISKEY});
    std::cout << std::boolalpha << l->canSit(b) << '\n';

    clear(l);
    clear(b);
    return 0;
}