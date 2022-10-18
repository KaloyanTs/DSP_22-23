#ifndef __MYSTRING_HPP
#define __MYSTRING_HPP
#include <iostream>
#include <cstring>

class myString
{
    static const unsigned sso = (1 << 4) - 1;
    char buf[sso + 1];
    char *data;

public:
    myString();
    myString(const char *);
    myString(char);
    myString(const myString &);
    myString(myString &&);
    myString &operator=(const myString &);
    myString &operator=(myString &&);
    unsigned length() const;
    const char *c_str() const;
    myString operator+(const myString &);
    myString &operator+=(const myString &);
    bool operator<(const myString &);
    bool operator<=(const myString &);
    bool operator>(const myString &);
    bool operator>=(const myString &);
    const char &front() const
    {
        if (data)
            return *data;
        return *buf;
    }
    const char &back() const
    {
        if (data)
            return data[length() - 1];
        return buf[length() - 1];
    }
    const char &operator[](unsigned n) const;
    ~myString();
    friend std::ostream &operator<<(std::ostream &os, const myString &s);
};

std::ostream &operator<<(std::ostream &os, const myString &s);

#endif