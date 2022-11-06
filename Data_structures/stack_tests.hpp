#include "doctest.h"
#include "stack.ipp"

TEST_CASE("След създаване на стек той е празен")
{
    stack<int> s;
    CHECK(s.empty());
}

TEST_CASE("Стекът не е празен след добавяне")
{
    stack<int> s;
    s.push(10);
    CHECK(!s.empty());
}

TEST_CASE("Елементите се изключват в ред обратен на включване")
{
    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    CHECK(!s.empty());
    CHECK_EQ(s.top(), 30);
    s.pop();
    CHECK_EQ(s.top(), 20);
    s.pop();
    CHECK_EQ(s.top(), 10);
    s.pop();
    CHECK(s.empty());
}

TEST_CASE("Top връща последно включения елемент")
{
    stack<int> s;
    s.push(10);
    CHECK_EQ(s.top(), 10);
    s.push(20);
    CHECK_EQ(s.top(), 20);
    s.pop();
    CHECK_EQ(s.top(), 10);
}

TEST_CASE("LinkedStack: неуспех при опит за поглеждане в празен стек")
{
    stack<int> s;
    CHECK_THROWS(s.top());
}

TEST_CASE("Изключение при опит за поглеждане в или изключване от празен стек")
{
    stack<int> s;
    CHECK_THROWS_AS(s.top(), std::runtime_error);
    CHECK_THROWS_AS(s.pop(), std::runtime_error);
}