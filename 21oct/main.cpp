#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

template <typename T>
typename std::vector<T>::const_iterator myFind(const std::vector<T> &v, const T &elem)
{
    typename std::vector<T>::const_iterator iter = v.cbegin();
    while (iter != v.cend() && *iter != elem)
        iter++;

    return iter;
}

template <typename T>
std::vector<T> reverse(const std::vector<T> &v)
{
    std::vector<T> res;
    typename std::vector<T>::const_reverse_iterator iter = v.crbegin();
    while (iter != v.crend())
    {
        res.push_back(*iter);
        iter++;
    }
    return res;
}

template <typename T>
bool isSubset(const std::vector<T> &set, const std::vector<T> &subset)
{
    typename std::vector<T>::const_iterator subIter = subset.cbegin();
    while (subIter != subset.cend() && myFind<T>(set, *subIter) != set.cend())
        ++subIter;
    return subIter == subset.cend();
}

template <typename T>
void map(std::vector<T> &v, void (*f)(T &))
{
    for (T &el : v)
        f(el);
}

template <typename T>
std::vector<T> filter(const std::vector<T> &v, bool (*p)(const T &))
{
    std::vector<T> res;
    for (const T &el : v)
        if (p(el))
            res.push_back(el);
    return res;
}

void square(int &n) { n *= n; }
bool isPrime(const unsigned &n)
{
    if (n < 2)
        return 0;
    unsigned sq = sqrt(n);
    unsigned i = 2;
    while (i <= sq && n % i != 0)
        ++i;
    return i > sq;
}

template <typename T>
void printVector(const std::vector<T> &v)
{
    for (const T &i : v)
        std::cout << i << ' ';
    std::cout << '\n';
}

std::vector<int>::const_iterator kThBiggest(const std::vector<int> &v, unsigned k)
{
    const int s = v.size();
    if (k > s)
        return std::vector<int>::const_iterator(v.cend());
    bool marked[s];
    for (bool &b : marked)
        b = false;
    unsigned index;
    int max;
    for (unsigned i = 0; i < k - 1; ++i)
    {
        index = 0;
        while (marked[index])
            ++index;
        max = v[index];
        for (unsigned j = index + 1; j < s; ++j)
            if (!marked[j] && v[j] > max)
            {
                index = j;
                max = v[j];
            }
        marked[index] = true;
    }

    index = 0;
    while (marked[index])
        ++index;
    max = v[index];
    for (unsigned j = index + 1; j < s; ++j)
        if (!marked[j] && v[j] > max)
        {
            index = j;
            max = v[j];
        }
    return std::vector<int>::const_iterator(v.begin() + index);
}

std::vector<int> uniqueElements(std::vector<int> v)
{
    std::vector<int> res;
    std::sort(v.begin(), v.end());
    std::vector<int>::const_iterator i = v.cbegin();
    while (i != v.cend())
    {
        if (i + 1 == v.cend() || i[1] != *i)
            res.push_back(*i);
        else
            while (i != v.cend() && *i == i[1])
                ++i;
        ++i;
    }
    return res;
}

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    typename std::vector<int>::const_iterator p = myFind(v, 3);
    if (p == v.end())
        std::cout << "not ";
    std::cout << "found\n";
    std::vector<int> vRev = reverse(v);
    printVector(vRev);
    std::cout << '\n';
    std::cout << std::boolalpha << isSubset(v, vRev) << '\n';
    vRev.push_back(6);
    std::cout << std::boolalpha << isSubset(v, vRev) << '\n';
    map(v, square);
    printVector(v);
    std::vector<unsigned> I_100;
    for (unsigned i = 1; i <= 100; ++i)
        I_100.push_back(i);
    std::vector<unsigned> primes_100 = filter(I_100, isPrime);
    printVector(primes_100);
    v.clear();
    v.push_back(1);
    v.push_back(9);
    v.push_back(7);
    v.push_back(8);
    v.push_back(3);
    v.push_back(1);
    v.push_back(3);
    v.push_back(4);
    std::cout << "4th biggest: " << *kThBiggest(v, 4) << '\n';
    v.clear();
    v.push_back(2);
    v.push_back(3);
    v.push_back(3);
    v.push_back(2);
    v.push_back(1);
    v.push_back(4);
    v.push_back(4);
    v.push_back(7);
    v.push_back(6);
    v.push_back(3);
    v.push_back(4);
    v = uniqueElements(v);
    printVector(v);
    return 0;
}