#include "doctest.h"
#include "queue.ipp"

TEST_CASE("След създаване на опашка, тя е празна")
{
    queue<int> q;
    CHECK(q.empty());
}

TEST_CASE("След добавяне на елемент в опашка, тя не е празна")
{
    queue<int> q;
    q.push(42);
    CHECK_FALSE(q.empty());
}

TEST_CASE("Опит за поглеждане в или изключване на елемент от празна опашка хвърля изключение")
{
    queue<int> q;
    CHECK_THROWS(q.front());
    CHECK_THROWS(q.pop());
}

TEST_CASE("При последователно добавяне на елементи в опашката се изключва първият добавен")
{
    queue<int> q;
    for (int i = 1; i <= 10; i++)
        q.push(i);
    CHECK_EQ(q.front(), 1);
    q.pop();
    CHECK_NE(q.front(), 1);
}

TEST_CASE("При последователно добавяне на елементи в опашката, се изключват в същия ред и след това опашката остава празна")
{
    queue<int> q;
    for (int i = 1; i <= 10; i++)
        q.push(i);
    CHECK_FALSE(q.empty());
    for (int i = 1; i <= 10; i++)
    {
        CHECK_EQ(q.front(), i);
        q.pop();
    }
    CHECK(q.empty());

    for (int i = 11; i <= 20; i++)
        q.push(i);
    CHECK_FALSE(q.empty());
    for (int i = 11; i <= 20; i++)
    {
        CHECK_EQ(q.front(), i);
        q.pop();
    }
    CHECK(q.empty());
}

TEST_CASE("Многократно добавяне и изключване на елементи")
{
    queue<int> q;
    for (int j = 0; j < 100; j++)
    {
        for (int i = 1; i <= 10; i++)
            q.push(i);
        CHECK_FALSE(q.empty());
        for (int i = 1; i <= 10; i++)
        {
            CHECK_EQ(q.front(), i);
            q.pop();
        }
        CHECK(q.empty());
    }
}