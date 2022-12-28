#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include <limits.h>

template <typename T>
struct NodeEl
{
    T value;
    NodeEl *left, *right;
    NodeEl(T _value, NodeEl *_left = nullptr, NodeEl *_right = nullptr)
        : value(_value), left(_left), right(_right) {}
    bool isLeaf() const { return !(left || right); }
};

using Node = NodeEl<int>;

template <typename T>
void printTree(const NodeEl<T> *root)
{
    if (!root)
    {
        std::cout << "()";
        return;
    }
    if (root->isLeaf())
    {
        std::cout << root->value;
        return;
    }
    std::cout << '(';
    printTree(root->left);
    std::cout << ' ' << root->value << ' ';
    printTree(root->right);
    std::cout << ')';
}

template <typename T>
void clearTree(NodeEl<T> *&root)
{
    if (!root)
        return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = nullptr;
}

Node *readTree(std::ifstream &ifs)
{
    size_t count, height;
    int read;
    char star;
    std::queue<Node *> q;
    ifs >> count >> height;
    ifs >> read;
    --count;
    Node *res = new Node(read);
    Node *currrent;
    q.push(res);
    while (!q.empty() && count)
    {
        currrent = q.front();
        q.pop();
        if (!currrent)
        {
            ifs >> star >> star;
            q.push(nullptr);
            q.push(nullptr);
        }
        else
        {
            ifs >> read;
            if (!ifs.eof() && !ifs.good())
            {
                q.push(nullptr);
                ifs.clear();
                ifs.seekg(1, std::ios::cur);
            }
            else
            {
                --count;
                currrent->left = new Node(read);
                q.push(currrent->left);
            }
            ifs >> read;
            if (!ifs.good())
            {
                q.push(nullptr);
                ifs.clear();
                ifs.seekg(1, std::ios::cur);
            }
            else
            {
                --count;
                currrent->right = new Node(read);
                q.push(currrent->right);
            }
        }
    }
    return res;
}

bool isBounded(const Node *root, int lBound, int uBound)
{
    if (!root)
        return true;
    return (root->value > lBound && root->value <= uBound) &&
           isBounded(root->left, lBound, root->value) &&
           isBounded(root->right, root->value, uBound);
}

bool isBST(const Node *root)
{
    return isBounded(root, INT_MIN, INT_MAX);
}

int kthBST(const Node *root, size_t k)
{
    std::stack<const Node *> st;
    const Node *current = root;
    ++k;
    while (k)
    {
        while (current)
        {
            st.push(current);
            current = current->left;
        }
        current = st.top();
        st.pop();
        --k;
        if (k)
            current = current->right;
    }
    return current->value;
}

Node *reprIter(const std::vector<int> &v,
               size_t from,
               size_t to)
{
    if (from == to)
        return nullptr;
    if (to - from == 1)
        return new Node(v.at(from));
    if (to - from == 2)
        return new Node(v.at(from + 1), new Node(v.at(from)), nullptr);
    size_t mid = (from + to) / 2;
    return new Node(v.at(mid), reprIter(v, from, mid), reprIter(v, mid + 1, to));
}

Node *represent(const std::vector<int> &v)
{
    return reprIter(v, 0, v.size());
}

std::vector<int> maxSumRec(const Node *root, int &sum)
{
    if (!root)
    {
        sum = 0;
        return std::vector<int>();
    }
    if (root->isLeaf())
    {
        std::vector<int> res;
        res.push_back(root->value);
        sum = root->value;
        return res;
    }
    int lSum, rSum;
    std::vector<int> l = maxSumRec(root->left, lSum);
    std::vector<int> r = maxSumRec(root->right, rSum);
    if (lSum > rSum)
    {
        l.push_back(root->value);
        sum += root->value;
        return l;
    }
    r.push_back(root->value);
    sum += root->value;
    return r;
}

std::vector<int> maxSum(const Node *root)
{
    int resSum;
    return maxSumRec(root, resSum);
}

NodeEl<char> *reprIter(const std::string &v,
                       size_t from,
                       size_t to)
{
    if (from == to)
        return nullptr;
    if (to - from == 1)
        return new NodeEl<char>(v.at(from));
    if (to - from == 2)
        return new NodeEl<char>(v.at(from + 1), new NodeEl<char>(v.at(from)), nullptr);
    size_t mid = (from + to) / 2;
    return new NodeEl<char>(v.at(mid), reprIter(v, from, mid), reprIter(v, mid + 1, to));
}

NodeEl<char> *represent(const std::string &v)
{
    return reprIter(v, 0, v.size());
}

std::string maxOccRec(const NodeEl<char> *root, char c, size_t &count)
{
    if (!root)
    {
        count = 0;
        return std::string();
    }
    if (root->isLeaf())
    {
        std::string res;
        res.push_back(root->value);
        count = root->value == c ? 1 : 0;
        return res;
    }
    size_t lcnt, rcnt;
    std::string l = maxOccRec(root->left, c, lcnt);
    std::string r = maxOccRec(root->right, c, rcnt);
    if (lcnt > rcnt)
    {
        l.push_back(root->value);
        count = lcnt + (root->value == c ? 1 : 0);
        return l;
    }
    r.push_back(root->value);
    count = rcnt + (root->value == c ? 1 : 0);
    return r;
}

std::string maxOcc(const NodeEl<char> *root, char c)
{
    size_t resOcc;
    return maxOccRec(root, c, resOcc);
}

int main()
{

    Node *t = new Node(20,
                       new Node(10,
                                new Node(8),
                                new Node(17,
                                         new Node(15))),
                       new Node(30,
                                new Node(25,
                                         new Node(23),
                                         nullptr),
                                new Node(33,
                                         new Node(31))));

    printTree(t);
    std::cout << '\n';
    clearTree(t);

    std::ifstream ifs;
    ifs.open("treeData.txt");
    if (!ifs.is_open())
        return -1;
    t = readTree(ifs);
    printTree(t);
    std::cout << '\n';
    ifs.close();
    size_t k = 0;
    if (!isBST(t))
        std::cout << "not a BST\n";
    else
    {
        std::cout << "BST\n";
        std::cin >> k;
        std::cout << kthBST(t, k) << '\n';
    }
    clearTree(t);

    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    t = represent(v);
    printTree(t);
    std::cout << '\n';
    std::vector<int> maxPath = maxSum(t);
    std::vector<int>::const_reverse_iterator i = maxPath.rbegin();
    while (i != maxPath.rend())
        std::cout << *i++ << ' ';
    std::cout << '\n';
    clearTree(t);

    std::string s = "caccacacasscgcgfcgccgccc";
    NodeEl<char> *t2 = represent(s);
    printTree(t2);
    std::cout << '\n';
    std::string maxPath2 = maxOcc(t2, 'c');
    // todo repair
    std::string::const_reverse_iterator i2 = maxPath2.crbegin();
    while (i2 != maxPath2.crend())
        std::cout << *i2++ << ' ';
    std::cout << '\n';
    clearTree(t2);

    return 0;
}