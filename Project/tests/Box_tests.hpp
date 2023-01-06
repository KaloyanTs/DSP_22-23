#ifndef __BOX_TESTS_HPP
#define __BOX_TESTS_HPP

#include "doctest.h"
#include "../Box.hpp"
#include <iostream>
#include <sstream>

TEST_CASE("Printing a box")
{
    Box *out = new Box("A");
    out->addSouvenir("Cup");
    Box *inner = new Box("C");
    inner->addSouvenir("Pen");
    out->addBox(inner);
    std::ostringstream s;
    s << *out;
    CHECK_EQ(s.str(), "A:\n\tCup\n\tC:\n\t\tPen\n");
}

TEST_CASE("Reading boxes from text file")
{
    std::list<Box> l = Box::readFromFile("boxesList.txt");
    std::ostringstream s;
    for (const Box &b : l)
        std::clog << b;
    for (const Box &b : l)
        s << b;
    CHECK_EQ(s.str(), "PlovdivBox:\n\tMagnet\n\tBook\n\tArtBox:\n\t\tDrawings:\n\t\t\tOldPlovdiv\n\tTheatreBox:\n\t\tTheatreSouvenirs:\n\t\t\tPlates:\n\t\t\t\tDecorativePlate\n\t\t\tBags:\nStaraZagoraBox:\n\tPostcard\n\tFigurines:\n\t\tAncientFigurine\n\tCups:\n\t\tTraditionalCup\n");
}

TEST_CASE("Optimizing boxes")
{
    SUBCASE("Example from description")
    {
        std::list<Box> l = Box::readFromFile("boxesList.txt");
        std::ostringstream s;
        for (Box &b : l)
        {
            b.optimize();
            s << b;
        }
        CHECK_EQ(s.str(), "PlovdivBox:\n\tMagnet\n\tBook\n\tDrawings:\n\t\tOldPlovdiv\n\tPlates:\n\t\tDecorativePlate\nStaraZagoraBox:\n\tPostcard\n\tFigurines:\n\t\tAncientFigurine\n\tCups:\n\t\tTraditionalCup\n");
    }

    SUBCASE("Highest level box becomes empty")
    {
        std::list<Box> l = Box::readFromFile("boxesListTest.txt");
        std::ostringstream s;
        for (Box &b : l)
        {
            b.optimize();
            s << b;
        }
        CHECK_EQ(s.str(), "B:\n\tS1\n\tS2\n");
    }
}

#endif