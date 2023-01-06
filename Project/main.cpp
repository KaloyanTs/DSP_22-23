// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

// #include "tests/SkipList_tests.hpp"
// #include "tests/Graph_tests.hpp"
// #include "tests/TrainMap_tests.hpp"
// #include "tests/CityMap_tests.hpp"
// #include "tests/Box_tests.hpp"

#include "TaskSolver.hpp"

int main()
{
    TaskSolver::total();
    std::cout << "Enter any key to exit...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}