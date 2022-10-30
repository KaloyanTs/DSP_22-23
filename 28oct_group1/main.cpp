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

int main()
{
    patients();
    patients2();

    return 0;
}