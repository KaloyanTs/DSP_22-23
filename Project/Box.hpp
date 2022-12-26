#ifndef __BOX_HPP
#define __BOX_HPP

#include <string>
#include <list>
#include <fstream>
#include <queue>
#include <map>

class Box
{
    std::string name;
    std::list<std::string> souvenirs;
    std::list<Box *> boxes;
    bool isContained;

    void print(std::ostream &os, unsigned level) const;

public:
    Box(const std::string &_name = "Unlabeled") : name(_name), isContained(false) {}
    Box(const Box &other);
    Box &operator=(const Box &) = delete;
    ~Box();

    static std::list<Box> readFromFile(const std::string &path);
    void optimize(Box &b);
    Box &addSouvenir(const std::string &s);
    Box &addBox(Box *b);
    friend std::ostream &operator<<(std::ostream &os, const Box &b);
};

#endif