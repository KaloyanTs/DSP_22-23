#include "Box.hpp"

void Box::print(std::ostream &os, unsigned level) const
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

Box::Box(const Box &other) : name(other.name), souvenirs(other.souvenirs), isContained(other.isContained)
{
    for (Box *b : other.boxes)
        boxes.push_back(new Box(*b));
}

Box::~Box()
{
    for (Box *b : boxes)
        delete b;
}

std::list<Box> Box::readFromFile(const std::string &path)
{
    std::ifstream ifs;
    ifs.open(std::string("data\\") + path);
    if (!ifs.is_open())
        return std::list<Box>();
    unsigned boxCount, count;
    ifs >> boxCount;
    ifs.ignore();
    std::string buf;

    using signedBox = std::pair<std::string, Box *>;
    std::map<std::string, Box *> data;

    //                  where   what
    std::queue<std::pair<Box *, std::string>> q;
    for (unsigned i = 0; i < boxCount; ++i)
    {
        ifs >> buf;
        Box *current = new Box(buf);
        data.insert(signedBox(buf, current));
        ifs >> count;
        ifs.ignore();
        for (unsigned j = 0; j < count; ++j)
        {
            ifs >> buf;
            current->addSouvenir(buf);
        }
        ifs >> count;
        ifs.ignore();
        for (unsigned j = 0; j < count; ++j)
        {
            ifs >> buf;
            q.push(std::pair<Box *, std::string>(current, buf));
        }
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
Box &Box::addSouvenir(const std::string &s)
{
    souvenirs.push_back(s);
    return *this;
}
Box &Box::addBox(Box *b)
{
    boxes.push_back(b);
    return *this;
}

void Box::optimize()
{

    std::list<Box *>::iterator cleaner = boxes.begin();
    while (cleaner != boxes.end())
    {
        (*cleaner)->optimize();
        if ((*cleaner)->empty())
        {
            delete *cleaner;
            boxes.erase(cleaner++);
        }
        else
            ++cleaner;
    }
    cleaner = boxes.begin();
    if (boxes.size() == 1 && souvenirs.empty())
    {
        for (Box *s : (*cleaner)->boxes)
        {
            boxes.push_back(s);
            s = nullptr;
        }
        for (const std::string &s : (*cleaner)->souvenirs)
            souvenirs.push_back(s);
        name = (*cleaner)->name;
        delete (*cleaner);
        boxes.erase(cleaner);
    }
}

std::ostream &operator<<(std::ostream &os, const Box &b)
{
    b.print(os, 0);
    return os;
}

std::list<Box> Box::solve(const std::string &path)
{
    std::list<Box> res = Box::readFromFile(path);
    std::list<Box>::iterator iter = res.begin();
    while (iter != res.end())
    {
        iter->optimize();
        if (iter->empty())
            res.erase(iter++);
        else
            ++iter;
    }
    return res;
}