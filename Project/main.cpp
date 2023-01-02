// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "doctest.h"

// #include "SkipList_tests.hpp"
// #include "Graph_tests.hpp"
// #include "TrainMap_tests.hpp"
// #include "CityMap_tests.hpp"
// #include "Box_tests.hpp"

#include "TaskSolver.hpp"

int main()
{
    TaskSolver::total();
    std::cout << "Enter any key to exit...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}