#include "BDZInterface.hpp"

const std::string BDZInterface::HELP_MSG = "\n-----------------------------------------------------------\nEnter 1 to see the most optimal journey;\nEnter 2 to see the most optimal walk inside a city;\nEnter 3 to see the most optimal box content;\nEnter 4 to see this message again;\nEnter 0 to exit.\n-----------------------------------------------------------\n";
const std::string BDZInterface::BOX_PATH = "boxesList.txt";

void BDZInterface::showShortestJourney(std::list<std::string> &j)
{
    std::cout << "Here is the shortest journey:\n";
    for (const std::string &c : j)
        std::cout << c << '\n';
}

void BDZInterface::showOptimalWalk(std::string &city, std::list<std::string> &w)
{
    std::cout << "Here is the optimal walk in " << city << ":\n";
    for (const std::string &landmark : w)
        std::cout << '\t' << landmark << '\n';
}

void BDZInterface::showBoxConfiguration(std::list<Box> &boxes)
{
    std::cout << "The optimal boxes configuration is:\n";
    for (const Box &b : boxes)
        std::cout << b;
}

void BDZInterface::showHelp() { std::cout << HELP_MSG; }

void BDZInterface::run()
{
    std::string pathToMap, pathToConstrains;
    std::cout << "Enter path to the train map file: ";
    std::cin >> pathToMap;
    std::cout << "Enter path to desired cities to visit file: ";
    std::cin >> pathToConstrains;
    std::list<std::string> res;
    try
    {
        res = TrainMap::solveShortestJourney(pathToMap, pathToConstrains);
    }
    catch (const std::exception &err)
    {
        std::cout << err.what() << '\n';
        std::cout << "Exiting...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::list<Box> boxes = Box::solve(BOX_PATH);
    showHelp();
    char cmd;
    do
    {
        cmd = getch();
        if (cmd == '4')
            showHelp();
        else if (cmd == '1')
            showShortestJourney(res);
        else if (cmd == '2')
        {
            std::string city;
            std::cout << "Enter name of city: ";
            std::cin >> city;
            std::list<std::string> tmp;
            tmp = CityMap::findBestWalk(city + ".txt");
            showOptimalWalk(city, tmp);
            std::cin.ignore();
        }
        else if (cmd == '3')
            showBoxConfiguration(boxes);
    } while (cmd != '0');
}