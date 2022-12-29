#ifndef __LIST_TESTS_HPP
#define __LIST_TESTS_HPP

#include "doctest.h"
#include "forward_list.ipp"
#include <cmath>

#define AllLists ForwardList<int>

TEST_CASE_TEMPLATE("При създаване на списък той е празен",
                   List, AllLists)
{
    List l;
    CHECK(l.empty());
}

TEST_CASE_TEMPLATE("При добавяне на елемент в списък той вече не е празен",
                   List, AllLists)
{
    List l;
    l.push_back(42);
    CHECK(!l.empty());
}

TEST_CASE_TEMPLATE("Последователно добавяне на елементи в списъка и обхождането му",
                   List, AllLists)
{
    List l;
    for (int i = 1; i <= 10; i++)
        l.push_back(i);

    int i = 1;
    for (int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Последователно добавяне на елементи в списъка от началото и обхождането му",
                   List, AllLists)
{
    List l;
    for (int i = 1; i <= 10; i++)
        l.push_front(i);

    int i = 10;
    for (int x : l)
        CHECK_EQ(i--, x);
    CHECK_EQ(i, 0);
}

TEST_CASE_TEMPLATE("Включване на елементи на четни позиции",
                   List, AllLists)
{
    List l;
    for (int i = 1; i <= 10; i += 2)
        l.push_back(i);
        
    for (typename List::Iterator it = l.begin(); it != l.end(); ++it, ++it)
        l.insertAfter(it, *it + 1);

    int i = 1;
    for (int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Последователно изтриване на последния елемент в списъка",
                   List, AllLists)
{
    List l;
    for (int i = 1; i <= 10; i++)
        l.push_front(i);

    int x;
    for (int i = 10; i >= 1; i--)
    {
        CHECK_EQ(l.front(), i);
        l.pop_front();
    }
    CHECK(l.empty());
}

TEST_CASE_TEMPLATE("Последователно изтриване на първия елемент в списъка",
                   List, AllLists)
{
    List l;
    for (int i = 1; i <= 10; i++)
        l.push_back(i);

    int x;
    for (int i = 1; i <= 10; i++)
    {
        CHECK_EQ(l.front(), i);
        l.pop_front();
    }
    CHECK(l.empty());
}

#endif