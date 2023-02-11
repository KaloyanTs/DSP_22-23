// Задача 1. Напишете функция която приема един аргумент – корен на дърво,
// чиито възли могат да имат произволен брой деца. Всеки възел пази стойност -- цяло число.
//
// Функцията трябва да намери онзи път от корена на дървото, до някое листо, който има най-малка
// сума на елементите в него. Този път трябва да се върне, като вектор от възлите в него.
// Ако има няколко такива пътя, може да се върне който и да е от тях. Напишете кратка програма,
// която демонстрира работата на функцията върху примерно дърво. По-долу са дадени представянето
// на дървото и прототипът на функцията, която трябва да реализирате. Те трябва да са точно такива,
// както са показани тук.
//
// struct Node {
//    int value;
//    std::vector<Node> children;
// };
//
// std::vector<Node*> findCheapestPath( Node* root )

#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
    int value;
    std::vector<Node> children;
    Node(int _value, const std::vector<Node> &l = {})
        : value(_value), children(l) {}
};

void print(Node &r)
{
    std::cout << "( " << r.value << ' ';
    for (Node &ch : r.children)
    {
        print(ch);
        std::cout << ' ';
    }
    std::cout << ')';
}

void clear(Node *&root)
{
    delete root;
    root = nullptr;
}

void rec(Node *root, std::vector<Node *> &best, int &bestSum)
{
    int sum = INT_MAX;
    std::vector<Node *> current;
    std::vector<Node *> bestPath;
    int currentSum = INT_MAX, bSum = INT_MAX;
    for (Node &n : root->children)
    {
        current.clear();
        currentSum = INT_MAX;
        rec(&n, current, currentSum);
        if (currentSum < bSum)
        {
            bestPath = std::move(current);
            bSum = currentSum;
        }
    }
    if (root->children.empty())
        bSum = 0;
    bSum += root->value;
    bestPath.push_back(root);
    if (bSum < bestSum)
    {
        best = std::move(bestPath);
        bestSum = bSum;
    }
}

std::vector<Node *> findCheapestPath(Node *root)
{
    std::vector<Node *> res;
    int bestSum = INT_MAX;
    rec(root, res, bestSum);
    std::reverse(res.begin(), res.end());
    return res;
}

int main()
{

    Node *t = new Node(3, {Node(2, {1,
                                    3}),
                           7,
                           4});

    print(*t);
    std::cout << '\n';

    std::vector<Node *> res = findCheapestPath(t);
    for (Node *r : res)
        std::cout << r->value << ' ';
    std::cout << '\n';

    clear(t);

    return 0;
}