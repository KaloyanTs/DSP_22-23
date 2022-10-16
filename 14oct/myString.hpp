#ifndef __MYSTRING_HPP
#define __MYSTRING_HPP

class myString
{
    static const unsigned sso = (1 << 4) - 1;
    char buf[sso + 1];
    char *data;
    unsigned capacity;

public:
    myString();
    myString(const char *);
    myString(char);
    myString(const myString &);
    myString(const myString &&);
    myString &operator=(const myString &);
    myString &operator=(const myString &&);
    unsigned length() const;
    const char *c_str() const;
    myString operator+(const myString &);
    myString operator+=(const myString &);
    ~myString();
};

#endif