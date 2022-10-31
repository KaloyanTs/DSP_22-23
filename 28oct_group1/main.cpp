#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <deque>

void patients()
{
    unsigned N;
    std::cin >> N;
    unsigned pCount;
    std::cin >> pCount;
    bool *urgent = new bool[pCount];
    for (unsigned i = 0; i < pCount; ++i)
        std::cin >> urgent[i];
    std::queue<unsigned> patients;
    std::stack<unsigned> urgentP;
    for (unsigned i = 0; i < pCount; ++i)
        if (urgent[i])
            urgentP.push(i + 1);
        else
            patients.push(i + 1);
    delete[] urgent;

    std::vector<std::queue<unsigned>> doctors;
    for (unsigned i = 0; i < N; ++i)
        doctors.push_back(std::queue<unsigned>());
    unsigned i = 0;
    while (!urgentP.empty())
    {
        doctors.at(i++).push(urgentP.top());
        urgentP.pop();
        if (i >= N)
            i = 0;
    }
    while (!patients.empty())
    {
        doctors.at(i++).push(patients.front());
        patients.pop();
        if (i >= N)
            i = 0;
    }

    for (i = 0; i < N; ++i)
    {
        std::cout << "doctor " << i + 1 << ": ";
        while (!doctors[i].empty())
        {
            std::cout << doctors.at(i).front() << ' ';
            doctors.at(i).pop();
        }
        std::cout << '\n';
    }
}

void patients2()
{
    unsigned N;
    std::cin >> N;
    unsigned pCount;
    std::cin >> pCount;
    bool *urgent = new bool[pCount];
    for (unsigned i = 0; i < pCount; ++i)
        std::cin >> urgent[i];
    std::deque<unsigned> patients;
    for (unsigned i = 0; i < pCount; ++i)
        if (urgent[i])
            patients.push_front(i + 1);
        else
            patients.push_back(i + 1);
    delete[] urgent;

    std::vector<std::queue<unsigned>> doctors;
    for (unsigned i = 0; i < N; ++i)
        doctors.push_back(std::queue<unsigned>());
    unsigned i = 0;
    while (!patients.empty())
    {
        doctors.at(i++).push(patients.front());
        patients.pop_front();
        if (i >= N)
            i = 0;
    }

    for (i = 0; i < N; ++i)
    {
        std::cout << "doctor " << i + 1 << ": ";
        while (!doctors[i].empty())
        {
            std::cout << doctors.at(i).front() << ' ';
            doctors.at(i).pop();
        }
        std::cout << '\n';
    }
}

template <typename T>
void equalize(std::vector<std::stack<T>> &L)
{
    unsigned total = 0;
    std::stack<T> buf;
    for (unsigned i = 0; i < L.size(); ++i)
    {
        total += L.at(i).size();
        while (!L.at(i).empty())
        {
            buf.push(L.at(i).top());
            L.at(i).pop();
        }
    }
    unsigned avg = total / L.size();
    for (unsigned i = 0; i < L.size(); ++i)
        for (unsigned j = 0; j < avg; ++j)
        {
            L.at(i).push(buf.top());
            buf.pop();
        }
    unsigned i = 0;
    while (!buf.empty())
    {
        L.at(i++).push(buf.top());
        buf.pop();
    }
}

int main()
{
    patients();
    patients2();
    std::vector<std::stack<int>> L;
    L.push_back(std::stack<int>());
    L.at(0).push(1);
    L.at(0).push(4);
    L.at(0).push(8);
    L.at(0).push(2);
    L.at(0).push(3);
    L.push_back(std::stack<int>());
    L.at(0).push(1);
    L.at(0).push(4);
    L.at(0).push(8);
    L.at(0).push(2);
    L.at(0).push(2);
    L.at(0).push(12);
    L.at(0).push(12);
    L.at(0).push(21);
    L.at(0).push(211);
    L.at(0).push(34);
    L.push_back(std::stack<int>());
    L.at(0).push(1);
    L.at(0).push(3);
    equalize(L);
    for (unsigned i = 0; i < L.size(); ++i)
    {
        std::cout << i + 1 << ": ";
        while (!L.at(i).empty())
        {
            std::cout << L.at(i).top() << ' ';
            L.at(i).pop();
        }
        std::cout << '\n';
    }
    return 0;
}