#include "doctest.h"
#include "SkipList.hpp"

using IntList = SkipList<int>;

TEST_CASE("Creating empty SkipList is indeed empty")
{
    IntList l;
    CHECK(l.empty());
}

TEST_CASE("Constructor with one parameters cretes non-empty SkipList")
{
    IntList l(1);
    CHECK_FALSE(l.empty());
}

TEST_CASE("Копирането на SkipList е коректно")
{
    // todo
    CHECK(true);
}

TEST_CASE("Принтиране на SkipList")
{
    // todo use ostringstream
    IntList l(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    std::cout << l << '\n';
    CHECK(true);
}

TEST_CASE("Addind element indeed works.")
{
}