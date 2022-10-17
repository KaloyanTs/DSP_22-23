#ifndef __MYSTRING_HPP
#define __MYSTRING_HPP

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
    ~myString();
};

#endif