#ifndef __MATRIX_HPP
#define __MATRIX_HPP
#include <iostream>

class Matrix
{
    static const unsigned size = 3;
    int data[size][size];

public:
    Matrix(const unsigned a[][3])
    {
        for (unsigned i = 0; i < size; ++i)
            for (unsigned j = 0; j < size; ++j)
                data[i][j] = a[i][j];
    }
    Matrix()
    {
        for (unsigned i = 0; i < size; ++i)
            for (unsigned j = 0; j < size; ++j)
                data[i][j] = 0;
    }
    Matrix operator+(const Matrix &other)
    {
        Matrix res;
        for (unsigned i = 0; i < size; ++i)
            for (unsigned j = 0; j < size; ++j)
                res.data[i][j] = data[i][j] + other.data[i][j];
        return res;
    }

    Matrix operator*(const Matrix &other)
    {
        Matrix res;
        for (unsigned i = 0; i < size; ++i)
            for (unsigned j = 0; j < size; ++j)
                for (unsigned k = 0; k < size; ++k)
                    res.data[i][j] += data[i][k] * other.data[k][j];
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
};

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    for (unsigned i = 0; i < m.size; ++i)
    {
        for (unsigned j = 0; j < m.size; ++j)
            std::cout << m.data[i][j] << '\t';
        os << '\n';
    }
    return os;
}

#endif