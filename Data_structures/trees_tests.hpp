#ifndef __TREES_TESTS_HPP
#define __TREES_TESTS_HPP

#include <sstream>
#include <cmath>
#include "doctest.h"
#include "binary_tree.ipp"
#include "binary_search_tree.ipp"
#include "avl_tree.ipp"

#define AllTrees BinaryTree<int>, BinarySearchTree<int>
#define OrderedTrees AVLTree<int>, BinarySearchTree<int>

TEST_CASE("Извеждане на примерно дърво на две нива")
{
    BinaryTree<int> t(1, BinaryTree<int>(2, BinaryTree<int>(3), BinaryTree<int>(4)), BinaryTree<int>(5, BinaryTree<int>(), BinaryTree<int>(6, BinaryTree<int>(7))));
    std::ostringstream os;
    t.print(os);
    CHECK_EQ(os.str(), "(1 (2 (3) (4)) (5 () (6 (7) ())))");
}

TEST_CASE("Работа с примерно дърво на четири нива")
{
    BinaryTree<int> t = BinaryTree<int>(1, BinaryTree<int>(2, BinaryTree<int>(3), BinaryTree<int>(4, BinaryTree<int>(5), BinaryTree<int>(6))), BinaryTree<int>(7, BinaryTree<int>(8), BinaryTree<int>(9, BinaryTree<int>(10))));

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

TEST_CASE_TEMPLATE("Наредено двоично дърво", Tree, OrderedTrees)
{
    Tree t(5);
    t.insert(3).insert(7).insert(4).insert(3).insert(9).insert(6).insert(8).insert(5);

    SUBCASE("Принтиране")
    {
        std::ostringstream os;
        t.print(os);
        CHECK_EQ(os.str(), "(5 (3 (3) (4 () (5))) (7 (6) (9 (8) ())))");
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

TEST_CASE("AVL дървото се самобалансира")
{
    AVLTree<int> t;
    CHECK_EQ(t.height(), 0);
    const size_t count = 100;

    for (unsigned i = 0; i < count; ++i)
    {
        t.insert(i);
        CHECK_EQ(t.height(), (int)log2(i + 1) + 1);
    }

    SUBCASE("при добавяне");
    {
        CHECK_EQ(t.height(), (int)log2(count) + 1);
    }

    SUBCASE("при премахване")
    {
        for (unsigned i = count; i > 0; --i)
        {
            CHECK_LE(t.height(), (int)log2(150 - i) + 3);
            REQUIRE(t.erase((i + (count >> 1)) % count));
        }
    }
}

int square(const int &x) { return x * x; }

TEST_CASE("събиране на стойностите в дърво")
{
    AVLTree<int> t;
    t.insert(1).insert(2).insert(3).insert(4).insert(5).insert(6).insert(7).insert(8);
    std::vector<int> res = t.collect<int>(square);
    for (unsigned i = 1; i <= res.size(); ++i)
        CHECK_EQ(res[i - 1], square(i));
}

#endif