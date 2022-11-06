#include <iostream>
#include "stack.ipp"
#include "queue.ipp"
#include "list.ipp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "stack_tests.hpp"
#include "queue_tests.hpp"
#include "list_tests.hpp"

// int main()
// {
//     stack<int> st;
//     st.push(1);
//     st.push(2);
//     st.push(6);
//     st.push(5);
//     st.push(3);
//     std::cout << st.top() << '\n';

//     while (!st.empty())
//     {
//         std::cout << st.top() << ' ';
//         st.pop();
//     }
//     std::cout << '\n';

//     queue<int> q;
//     q.push(1);
//     q.push(2);
//     q.push(6);
//     q.push(5);
//     q.push(3);
//     std::cout << q.front() << '\n';

//     while (!q.empty())
//     {
//         std::cout << q.front() << ' ';
//         q.pop();
//     }
//     std::cout << '\n';

//     list<int> l;
//     l.push_back(1);
//     l.push_back(2);
//     l.push_back(6);
//     l.push_back(5);
//     l.push_back(3);
//     std::cout << l.front() << '\n';

//     while (!l.empty())
//     {
//         std::cout << l.back() << ' ';
//         l.pop_front();
//     }
//     std::cout << '\n';

//     try
//     {
//         l.pop_front();
//     }
//     catch (...)
//     {
//         std::cout << "error occured\n";
//     }

//     return 0;
// }