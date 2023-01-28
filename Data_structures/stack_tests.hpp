#include "doctest.h"
#include "linked_stack.ipp"
#include "static_stack.ipp"
#include "dynamic_stack.ipp"

#define AllStacks StaticStack<int>, LinkedStack<int>, DynamicStack<int>

TEST_CASE("След създаване на стек той е празен", Stack, AllStacks)
{
    Stack s;
    CHECK(s.empty());
}

TEST_CASE("Конструктор за копиране", Stack, AllStacks)
{
    Stack s1;
    s1.push(3);
    s1.push(2);
    s1.push(1);
    Stack s2 = s1;
    CHECK_EQ(s1.top(), s2.top());
    s1.pop();
    s2.pop();
    CHECK_EQ(s1.top(), s2.top());
    s1.pop();
    s2.pop();
    CHECK_EQ(s1.top(), s2.top());
    s1.pop();
    s2.pop();
    CHECK_EQ(s1.empty(), s2.empty());
}

TEST_CASE("Стекът не е празен след добавяне", Stack, AllStacks)
{
    Stack s;
    s.push(10);
    CHECK(!s.empty());
}

TEST_CASE("Елементите се изключват в ред обратен на включване", Stack, AllStacks)
{
    Stack s;
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

TEST_CASE("Top връща последно включения елемент", Stack, AllStacks)
{
    Stack s;
    s.push(10);
    CHECK_EQ(s.top(), 10);
    s.push(20);
    CHECK_EQ(s.top(), 20);
    s.pop();
    CHECK_EQ(s.top(), 10);
}

TEST_CASE("Изключение при опит за поглеждане или изключване от празен стек", Stack, AllStacks)
{
    Stack s;
    CHECK_THROWS_AS(s.top(), std::runtime_error);
    CHECK_THROWS_AS(s.pop(), std::runtime_error);
}

TEST_CASE("Размяна на съдържанието на два стека", Stack, AllStacks)
{
    Stack s1;
    s1.push(3);
    s1.push(2);
    s1.push(1);
    Stack s2;
    s2.push(5);
    s2.push(4);
    s1.swap(s2);
    CHECK_EQ(s1.top(), 4);
    s1.pop();
    CHECK_EQ(s1.top(), 5);
    s1.pop();
    CHECK(s1.empty());

    CHECK_EQ(s2.top(), 1);
    s2.pop();
    CHECK_EQ(s2.top(), 2);
    s2.pop();
    CHECK_EQ(s2.top(), 3);
    s2.pop();
    CHECK(s2.empty());
}