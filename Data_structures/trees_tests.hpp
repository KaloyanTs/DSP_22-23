#ifndef __TREES_TESTS_HPP
#define __TREES_TESTS_HPP

#include <sstream>
#include "doctest.h"
#include "binary_tree.ipp"
#include "binary_search_tree.ipp"

#define AllTrees BinaryTree<int>, BinarySearchTree<int>

TEST_CASE_TEMPLATE("Извеждане на примерно дърво на две нива", Tree, AllTrees)
{
    Tree t(1, Tree(2, Tree(3), Tree(4)), Tree(5, Tree(), Tree(6, Tree(7))));
    std::ostringstream os;
    t.print(os);
    CHECK_EQ(os.str(), "(1 (2 (3) (4)) (5 () (6 (7) ())))");
}

TEST_CASE_TEMPLATE("Работа с примерно дърво на четири нива", Tree, AllTrees)
{
    Tree t = Tree(1, Tree(2, Tree(3), Tree(4, Tree(5), Tree(6))), Tree(7, Tree(8), Tree(9, Tree(10))));

    SUBCASE("Извеждане")
    {
        std::ostringstream os;
        t.print(os);
        CHECK_EQ(os.str(), "(1 (2 (3) (4 (5) (6))) (7 (8) (9 (10) ())))");
    }

    SUBCASE("Дълбочина")
    {
        CHECK_EQ(t.depth(), 4);
    }
}

TEST_CASE("Наредено двоично дърво")
{
    BinarySearchTree<int> t(5);
    t.insert(3).insert(7).insert(4).insert(3).insert(9).insert(6).insert(8).insert(5);

    SUBCASE("Принтиране")
    {
        std::ostringstream os;
        t.print(os);
        CHECK_EQ(os.str(), "(5 (3 (3) (4 () (5))) (7 (6) (9 (8))))");
    }

    SUBCASE("Търсене на елемент")
    {
        CHECK(t.search(4));
        CHECK(t.search(8));
        CHECK_FALSE(t.search(1));
        CHECK_FALSE(t.search(10));
    }

    SUBCASE("Дървото е наредено")
    {
        std::ostringstream os;
        t.leftToRight(os);
        CHECK_EQ(os.str(), "3 3 4 5 5 6 7 8 9");
    }
}

#endif