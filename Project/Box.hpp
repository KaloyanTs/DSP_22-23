#ifndef __BOX_HPP
#define __BOX_HPP

#include <string>
#include <list>

using Label = std::string;

class Box
{
    Label name;
    std::list<std::string> souvenirs;
    std::list<Box> boxes;

public:
    Box(const Label &_name = "Unlabeled") : name(_name) {}
    //todo implement
    static std::list<Box> readFromFile(const std::string &path);
    //todo implement
    static void optimize(Box &b);
    Box &addSouvenir(const std::string &s)
    {
        souvenirs.push_back(s);
    }
    Box &addBox(const Box &b)
    {
        boxes.push_back(b);
    }
}

#endif