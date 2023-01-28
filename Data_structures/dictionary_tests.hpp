#ifndef __DICTIONARY_TESTS_HPP
#define __DICTIONARY_TESTS_HPP

#include <iostream>
#include <sstream>
#include <string>
#include "doctest.h"
#include "hash_table.ipp"
#include "avl_dictionary.ipp"

unsigned hashString(const std::string &key)
{
    unsigned sum = 0;
    for (char c : key)
        sum += c;
    return sum;
}

#define ALL_DICTIONARIES AVLDictionary<std::string, int> //, HashTable<std::string, int, hashString>

TEST_CASE_TEMPLATE("Добавяне на елемент в празен речник", Dictionary, ALL_DICTIONARIES)
{
    Dictionary dict;
    CHECK_EQ(dict.find("the_answer"), nullptr);
    dict.set("the_answer", 42);
    CHECK_EQ(*dict.find("the_answer"), 42);
    dict.set("the_answer", 43);
}

TEST_CASE_TEMPLATE("Добавяне и изтриване на елементи", Dictionary, ALL_DICTIONARIES)
{

    Dictionary dict;
    for (int x : {12, 42, 135, 15, 7})
        dict.set(std::to_string(x), x);

    SUBCASE("Можем да намерим всички добавени елементи")
    {
        for (int x : {12, 42, 135, 15, 7})
            CHECK_EQ(*dict.find(std::to_string(x)), x);
    }

    SUBCASE("Не можем да изтрием липсващ елемент")
    {
        CHECK(!dict.erase("missing"));
    }

    SUBCASE("Изтриваме успешно съществуващи елементи")
    {
        REQUIRE(dict.erase("135"));
        REQUIRE(dict.erase("15"));

        CHECK_EQ(dict.find("135"), nullptr);
        CHECK_EQ(dict.find("15"), nullptr);
        CHECK_EQ(*dict.find("12"), 12);
        CHECK_EQ(*dict.find("42"), 42);
        CHECK_EQ(*dict.find("7"), 7);
    }

    SUBCASE("Изброяваме коректно ключовете")
    {
        size_t len = 0;
        for (std::string key : dict.keys())
        {
            CHECK((key == "135" || key == "15" || key == "42" || key == "7" || key == "12"));
            len++;
        }
        CHECK_EQ(len, 5);
    }

    SUBCASE("Изброяваме коректно стойностите")
    {
        size_t len = 0;
        for (unsigned value : dict.values())
        {
            CHECK((value == 135 || value == 15 || value == 42 || value == 7 || value == 12));
            len++;
        }
        CHECK_EQ(len, 5);
    }
}

TEST_CASE_TEMPLATE("Добавяне и изтриване на 100 елемента", Dictionary, ALL_DICTIONARIES)
{
    Dictionary dict;
    for (int i = 1; i <= 50; i++)
    {
        dict.set(std::to_string(i), i);
        dict.set(std::to_string(101 - i), 101 - i);
    }

    for (int i = 1; i <= 100; i++)
        CHECK_EQ(*dict.find(std::to_string(i)), i);

    for (int i = 50; i > 10; i--)
    {
        CHECK(dict.erase(std::to_string(i)));
        CHECK(dict.erase(std::to_string(101 - i)));
    }

    for (int i = 11; i <= 90; i++)
        CHECK_EQ(dict.find(std::to_string(i)), nullptr);

    for (int i = 1; i <= 10; i++)
    {
        CHECK_EQ(*dict.find(std::to_string(i)), i);
        CHECK_EQ(*dict.find(std::to_string(101 - i)), 101 - i);
    }

    dict["5"] = 55;
    CHECK_EQ(dict["5"], 55);
}

#endif