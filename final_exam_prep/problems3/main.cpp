#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

struct Node
{
    int val;
    std::vector<Node *> children;
    Node(int v, const std::vector<Node *> &ch = {})
        : val(v), children(ch) {}
};

void print(Node *root)
{
    if (!root)
    {
        std::cout << "()";
        return;
    }
    std::cout << "( " << root->val;
    for (Node *ch : root->children)
    {
        std::cout << ' ';
        print(ch);
    }
    std::cout << " )";
}

void clear(Node *&root)
{
    if (!root)
        return;
    for (Node *&r : root->children)
        clear(r);
    delete root;
    root = nullptr;
}

std::unordered_map<Node *, int> levels(Node *root)
{
    std::stack<std::pair<Node *, int>> st;
    std::unordered_map<Node *, int> m;
    st.push(std::pair<Node *, int>(root, 0));
    Node *current;
    int lvl;
    while (!st.empty())
    {
        current = st.top().first;
        lvl = st.top().second;
        m[current] = lvl;
        for (Node *ch : current->children)
            st.push(std::pair<Node *, int>(ch, lvl + 1));
    }
    return m;
}

bool canBeSame(Node *t1, Node *t2)
{
    if (!t2)
        return !t1;
    if (!t1)
        return false;
    if (t1->val != t2->val || t1->children.size() != t2->children.size())
        return false;
    
}

int main()
{
    Node *t1 = new Node(4, {new Node(2, {new Node(6)}),
                            new Node(5, {new Node(3),
                                         new Node(7, {new Node(8)})}),
                            new Node(1)});

    Node *t2 = new Node(5, {new Node(8, {new Node(6)}),
                            new Node(2, {new Node(7, {new Node(8)})}),
                            new Node(5)});

    print(t1);
    std::cout << '\n';
    print(t2);
    std::cout << '\n';

    clear(t1);
    clear(t2);

    return 0;
}