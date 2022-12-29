#ifndef __TREES_TESTS_HPP
#define __TREES_TESTS_HPP

#include <sstream>
#include "doctest.h"
#include "binary_tree.ipp"
#include "binary_search_tree.ipp"

using IntTree = BinaryTree<int>;

TEST_CASE_TEMPLATE("Извеждане на примерно дърво на две нива")
{
    IntTree t 

    std::ostringstream os;
    t.print(os);
    CHECK_EQ(os.str(), "(1 (2) (9) (10))");
}

TEST_CASE_TEMPLATE("Работа с примерно дърво на четири нива")
{
    IntTree t =
        IntTree(1)
        << (IntTree(2)
            << IntTree(3)
            << (IntTree(4)
                << IntTree(5)
                << IntTree(6))
            << IntTree(7)
            << IntTree(8))
        << IntTree(9)
        << IntTree(10);

    SUBCASE("Извеждане")
    {
        std::ostringstream os;
        t.print(os);
        CHECK_EQ(os.str(), "(1 (2 (3) (4 (5) (6)) (7) (8)) (9) (10))");
    }

    SUBCASE("Дълбочина")
    {
        CHECK_EQ(t.depth(), 4);
    }

    SUBCASE("Ширина")
    {
        CHECK_EQ(t.breadth(), 4);
    }
}

TEST_CASE_TEMPLATE("Празният конструк")

#endif