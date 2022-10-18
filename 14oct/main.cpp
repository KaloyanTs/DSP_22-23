#include <iostream>
#include <cmath>
#include "Matrix.hpp"
#include "myString.hpp"

unsigned productDigits(unsigned a, unsigned b)
{
    return floor(log10(a) + log10(b) + 1);
}

bool isPrime(unsigned n)
{
    if (n < 2)
        return false;
    unsigned i = 2, sq = sqrt(n);
    while (i <= sq && n % i)
        ++i;
    return i > sq;
}

void nPrimes(unsigned n)
{
    bool *primes = new bool[n + 1];
    for (unsigned i = 2; i <= n; i++)
        primes[i] = true;

    for (unsigned i = 2; i <= n; ++i)
        if (primes[i])
            for (unsigned j = i * i; j <= n; j += i)
                primes[j] = false;

    for (unsigned i = 2; i <= n; ++i)
        if (primes[i])
            std::cout << i << '\n';

    delete[] primes;
}

void factor(unsigned n)
{
    unsigned p = 2;
    while (n != 1)
        if (n % p == 0)
        {
            n /= p;
            std::cout << p;
            if (n != 1)
                std::cout << '*';
        }
        else
            ++p;
}

void sumsSolve(unsigned, unsigned *, unsigned);
void sums(unsigned n)
{
    unsigned *buf = new unsigned[n];
    sumsSolve(n, buf, 0);
    delete[] buf;
}

void sumsSolve(unsigned n, unsigned *s, unsigned count)
{
    if (!n)
    {
        for (unsigned i = 0; i < count; ++i)
        {
            if (i)
                std::cout << " + ";
            std::cout << s[i];
        }
        std::cout << '\n';
        return;
    }
    unsigned min = 1;
    if (count)
        min = s[count - 1];
    for (unsigned i = min; i <= n; ++i)
    {
        s[count] = i;
        sumsSolve(n - i, s, count + 1);
    }
}

unsigned **sumMatrices(const unsigned *a[3], const unsigned *b[3], unsigned m, unsigned n, unsigned *res[3])
{
    for (unsigned i = 0; i < m; ++i)
        for (unsigned j = 0; j < n; ++j)
            res[i][j] = a[i][j] + b[i][j];
    return res;
}

int main()
{

    unsigned a = 3242;
    unsigned b = 322;
    std::cout << productDigits(a, b) << '\n'
              << a * b << '\n';
    std::cout << isPrime(108) << '\n';
    const unsigned n = 100;
    std::cout << "primes to " << n << '\n';
    nPrimes(n);
    std::cout << "factoring of " << n << ": " << n << " = ";
    factor(n);
    std::cout << "\nAll possible sums of " << n / 15 << ":\n";
    sums(n / 15);
    const unsigned m1[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const unsigned m2[][3] = {{8, 3, 1}, {1, 4, 2}, {0, 3, 5}};
    Matrix M1(m1);
    Matrix M2(m2);
    std::cout << M1 + M2;
    myString s("sdfdd");
    std::cout << s + " ewrwr" << '\n';
    return 0;
}