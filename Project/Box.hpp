#ifndef __BOX_HPP
#define __BOX_HPP

#include <string>
#include <list>
#include <fstream>
#include <queue>
#include <map>

using Label = std::string;

const unsigned MAX_INPUT_LENGTH = 128;

class Box
{
    Label name;
    std::list<std::string> souvenirs;
    std::list<Box *> boxes;
    bool isContained;

    void print(std::ostream &os, unsigned level) const
    {
        std::string indent = "";
        for (unsigned i = 0; i < level; ++i)
            indent += '\t';
        os << indent << name << ":\n";
        for (const std::string &s : souvenirs)
            os << indent << '\t' << s << '\n';
        for (const Box *b : boxes)
            b->print(os, level + 1);
    }

public:
    // todo change char* with strings
    Box(const Label &_name = "Unlabeled") : name(_name), isContained(false) {}
    Box(const Box &other) : name(other.name), souvenirs(other.souvenirs), isContained(other.isContained)
    {
        for (Box *b : other.boxes)
            boxes.push_back(new Box(*b));
    }
    Box &operator=(const Box &) = delete;
    ~Box()
    {
        for (Box *b : boxes)
            delete b;
    }

    static std::list<Box> readFromFile(const std::string &path)
    {
        std::ifstream ifs;
        ifs.open(std::string("data\\") + path);
        if (!ifs.is_open())
            return std::list<Box>();
        unsigned boxCount, count;
        ifs >> boxCount;
        ifs.ignore();
        char buf[MAX_INPUT_LENGTH];

        using signedBox = std::pair<std::string, Box *>;
        std::map<std::string, Box *> data;

        //                  where   what
        std::queue<std::pair<Box *, std::string>> q;
        for (unsigned i = 0; i < boxCount; ++i)
        {
            ifs >> buf;
            std::cout << "Box name: " << buf << '\t'; // todo
            Box *current = new Box(buf);
            data.insert(signedBox(buf, current));
            ifs >> count;
            std::cout << "Souvenirs count: " << count << '\t'; // todo
            ifs.ignore();
            for (unsigned j = 0; j < count; ++j)
            {
                ifs >> buf;
                std::cout << "Souvenir name: " << buf << '\t';
                current->addSouvenir(buf);
            }
            ifs >> count;
            std::cout << "SubBoxes count: " << count << '\t'; // todo
            ifs.ignore();
            for (unsigned j = 0; j < count; ++j)
            {
                ifs >> buf;
                std::cout << "SubBox name: " << buf << '\t'; // todo
                q.push(std::pair<Box *, std::string>(current, buf));
            }
            std::cout << '\n'; // todo
        }
        ifs.close();

        while (!q.empty())
        {
            std::pair<Box *, std::string> &task = q.front();
            Box *toBePut = data[task.second];
            task.first->addBox(toBePut);
            toBePut->isContained = true;
            q.pop();
        }

        std::map<std::string, Box *>::iterator cleaner = data.begin();
        while (cleaner != data.end())
        {
            std::cout << cleaner->first << '\n';
            if (cleaner->second->isContained)
                data.erase(cleaner++);
            else
                ++cleaner;
        }
        std::list<Box> res;
        for (std::pair<std::string, Box *> p : data)
        {
            res.push_back(*p.second);
            delete p.second;
        }
        return res;
    }
    // todo implement
    static void optimize(Box &b);
    Box &addSouvenir(const std::string &s)
    {
        souvenirs.push_back(s);
        return *this;
    }
    Box &addBox(Box *b)
    {
        boxes.push_back(b);
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &os, const Box &b);
};

std::ostream &operator<<(std::ostream &os, const Box &b)
{
    b.print(os, 0);
    return os;
}

#endif