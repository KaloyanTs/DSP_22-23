#include <iostream>
#include <vector>
#include <queue>

struct Node
{
    int val;
    Node *left, *right;
    Node(int _val, Node *l = nullptr, Node *r = nullptr) : val(_val), left(l), right(r) {}
};

void insert(Node *&root, int val)
{
    if (!root)
    {
        root = new Node(val);
        return;
    }
    if (root->val >= val)
        insert(root->left, val);
    else
        insert(root->right, val);
}

bool remove(Node *&root, int el)
{
    if (!root)
        return false;
    if (root->val < el)
        return remove(root->right, el);
    if (root->val > el)
        return remove(root->left, el);

    if (!root->left)
    {
        Node *tmp = root;
        root = root->right;
        delete tmp;
        return true;
    }
    if (!root->right)
    {
        Node *tmp = root;
        root = root->left;
        delete tmp;
        return true;
    }
    Node *rightMost = root->left;
    Node *prev = nullptr;
    while (rightMost->right)
    {
        prev = rightMost;
        rightMost = rightMost->right;
    }
    if (!prev)
    {
        rightMost->right = root->right;
        delete root;
        root = rightMost;
        return true;
    }
    Node *l = rightMost->left;
    rightMost->left = root->left;
    rightMost->right = root->right;
    prev->right = l;
    delete root;
    root = rightMost;
    return true;
}

void clear(Node *&root)
{
    if (!root)
        return;
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

void print(Node *root)
{
    if (!root)
    {
        std::cout << "()";
        return;
    }
    if (!root->left && !root->right)
    {
        std::cout << '(' << root->val << ')';
        return;
    }
    std::cout << '(' << root->val << ' ';
    print(root->left);
    std::cout << ' ';
    print(root->right);
    std::cout << ')';
}

std::vector<int> levelMeans(Node *root)
{
    std::vector<int> res;
    if (!root)
        return res;
    std::queue<Node *> q;
    q.push(root);
    size_t count = 0, nextCount = 1, iter = 0;
    int sum;
    while (!q.empty())
    {
        count = nextCount;
        iter = count;
        nextCount = 0;
        sum = 0;
        while (iter)
        {
            root = q.front();
            q.pop();
            sum += root->val;
            --iter;
            if (root->left)
            {
                ++nextCount;
                q.push(root->left);
            }
            if (root->right)
            {
                ++nextCount;
                q.push(root->right);
            }
        }
        res.push_back(sum / count);
    }
    return res;
}

int main()
{
    Node *t = new Node(4);
    insert(t, 6);
    insert(t, 5);
    insert(t, 6);
    insert(t, 3);
    insert(t, 2);

    print(t);
    std::cout << '\n';

    std::vector<int> means = levelMeans(t);
    for (int a : means)
        std::cout << a << ' ';
    std::cout << '\n';

    remove(t, 6);
    print(t);

    clear(t);
    return 0;
}