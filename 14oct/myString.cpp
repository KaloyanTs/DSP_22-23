#include "myString.hpp"
#include <iostream>
#include <cstring>

myString::myString() : data(nullptr)
{
    *buf = '\0';
}

myString::myString(const char *str)
{
    if (strlen(str) > sso)
    {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    else
    {
        data = nullptr;
        strcpy(buf, str);
    }
}

myString::myString(char c) : data(nullptr)
{
    *buf = c;
    buf[1] = '\0';
}

myString::myString(const myString &other)
{
    if (other.data)
        data = new char[other.length() + 1];
    strcpy(data, other.data);
}

myString::myString(myString &&other)
{
    if (other.data)
    {
        data = other.data;
        other.data = nullptr;
    }
    else
    {
        data = nullptr;
        strcpy(buf, other.buf);
    }
}

myString &myString::operator=(myString &&other)
{
    if (data)
        delete[] data;
    if (other.data)
    {
        data = other.data;
        other.data = nullptr;
    }
    else
    {
        data = nullptr;
        strcpy(buf, other.buf);
    }
}

unsigned myString::length() const
{
    if (data)
        return strlen(data);
    return strlen(buf);
}

const char *myString::c_str() const
{
    if (data)
        return data;
    return buf;
}

myString myString::operator+(const myString &other)
{
    myString res;
    unsigned thisL = length(), otherL = other.length();
    if (length() + other.length() > myString::sso)
    {
        res.data = new char[thisL + otherL + 1];
        strcpy(res.data, this->c_str());
        strcat(res.data, other.c_str());
    }
    else
    {
        strcpy(res.buf, this->c_str());
        strcat(res.buf, other.c_str());
    }
    return res;
}

myString &myString::operator+=(const myString &other)
{
    return *this = *this + other;
}

myString::~myString()
{
    if (data)
        delete[] data;
}

bool myString::operator<(const myString &other)
{
    const char *t = c_str(), *o = other.c_str();
    while (*t == *o)
    {
        ++t;
        ++o;
    }
    if (!*t || !*o)
        return !*t;
    return *t < *o;
}

bool myString::operator<=(const myString &other)
{
    return !(*this > other);
}

bool myString::operator>(const myString &other)
{
    const char *t = c_str(), *o = other.c_str();
    while (*t == *o)
    {
        ++t;
        ++o;
    }
    if (!*t || !*o)
        return !*o;
    return *t > *o;
}

bool myString::operator>=(const myString &other)
{
    return !(*this < other);
}
