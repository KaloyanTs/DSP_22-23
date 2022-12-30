#include "TaskSolver.hpp"

#include <iostream>

void TaskSolver::total()
{
    std::string pathToMap, pathToConstrains;
    std::cout << "Enter path to the train map file: ";
    std::cin >> pathToMap;
    std::cout << "Enter path to desired cities to visit file: ";
    std::cin >> pathToConstrains;
    std::list<std::string> res = TrainMap::solveShortestJourney(pathToMap, pathToConstrains);
    std::cout << "Here is the shortest journey:\n";
    for (const std::string &c : res)
        std::cout << c << '\n';
    std::cin.ignore();
    std::cin.get();
    std::list<std::string> tmp;
    for (const std::string &c : res)
    {
        tmp = CityMap::findBestWalk(c + ".txt");
        std::cout << "Here is the optimal walk in " << c << ":\n";
        for (const std::string &landmark : tmp)
            std::cout << '\t' << landmark << '\n';
        std::cin.ignore();
        std::cin.get();
    }
    TaskSolver::c();
}

void TaskSolver::a()
{
    std::string pathToMap, pathToConstrains;
    std::cout << "Enter path to the train map file: ";
    std::cin >> pathToMap;
    std::cout << "Enter path to desired cities to visit file: ";
    std::cin >> pathToConstrains;
    std::list<std::string> res = TrainMap::solveShortestJourney(pathToMap, pathToConstrains);
    std::cout << "Here is the shortest journey:\n";
    for (const std::string &c : res)
        std::cout << c << '\n';
    std::cin.ignore();
    std::cin.get();
}

void TaskSolver::b()
{
    std::string pathToMap;
    std::cout << "Enter path to the map of the city file: ";
    std::cin >> pathToMap;
    std::list<std::string> res = CityMap::findBestWalk(pathToMap);
    std::cout << "Here is the optimal walk:\n";
    for (const std::string &c : res)
        std::cout << c << '\n';
    std::cin.ignore();
    std::cin.get();
}

void TaskSolver::c()
{
    std::list<Box> l = Box::solve("boxesList.txt");
    std::cout << "The optimal boxes configuration is:\n";
    for (const Box &b : l)
        std::cout << b;
    std::cin.get();
}