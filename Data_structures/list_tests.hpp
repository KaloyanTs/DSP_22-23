#include "doctest.h"
#include "list.ipp"

TEST_CASE("Списъкът е празен по подразбиране")
{
    list<int> l;
    CHECK(l.empty());
}