#include <iostream>
#include <vector>
#include <algorithm>

bool less(const int &a, const int &b)
{
    return a > b;
}

int main()
{
    std::vector<int> v;
    v.push_back(3);
    v.push_back(5);
    v.push_back(2);
    v.push_back(1);
    v.push_back(6);
    v.push_back(9);
    v.push_back(2);
    v.push_back(6);
    std::sort(v.begin(), v.end(),less);
    for (int a : v)
        std::cout << a << ' ';
    std::cout << '\n';
    return 0;
}