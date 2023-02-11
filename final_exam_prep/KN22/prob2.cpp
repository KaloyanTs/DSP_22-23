#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_set>
#include <exception>
#include <algorithm>

struct Node
{
    int val;
    std::vector<Node *> children;
    Node(int _val) : val(_val) {}
};

void print(Node *root)
{
    std::cout << "( " << root->val;
    for (Node *&ch : root->children)
    {
        std::cout << ' ';
        print(ch);
    }
    std::cout << " )";
}

void clear(Node *&root)
{
    for (Node *&ch : root->children)
        clear(ch);
    delete root;
    root = nullptr;
}

Node *readTree(const std::string &path)
{
    std::ifstream ifs(path);
    if (!ifs.is_open())
        throw std::runtime_error("No such file found...");
    Node *root{nullptr};
    std::queue<Node *> q;
    int val;
    Node *current;
    ifs.ignore();
    ifs >> val;
    ifs.ignore();
    ifs.ignore();
    ifs.ignore();
    root = new Node(val);
    q.push(root);
    std::unordered_set<int> s;
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        ifs.ignore();
        s.clear();
        do
        {
            ifs >> val;
            if (!ifs.good())
                break;
            if (s.count(val))
                throw std::exception();
            s.insert(val);
            current->children.push_back(new Node(val));
            q.push(current->children.back());
        } while (true);
        ifs.clear();
        ifs.ignore();
        if (ifs.peek() == '\n')
            ifs.ignore();
    }

    ifs.close();
    return root;
}

bool isSubtreeFrom(Node *from, Node *small)
{
    if (from->val != small->val)
        return false;
    bool exists;
    for (Node *chsmall : small->children)
    {
        exists = false;
        for (Node *chbig : from->children)
            if (chbig->val == chsmall->val)
            {
                if (!isSubtreeFrom(chbig, chsmall))
                    return false;
                exists = true;
            }
        if (!exists)
            return false;
    }
    return true;
}

bool isSubtree(Node *big, Node *small)
{
    if (!small)
        return true;
    if (!big)
        return false;
    bool res = true;
    if (big->val == small->val && isSubtreeFrom(big, small))
        return true;
    for (Node *ch : big->children)
        if (isSubtree(ch, small))
            return true;
    return false;
}

int treeSum(Node *t)
{
    int res = t->val;
    for (Node *ch : t->children)
        res += ch->val;
    return res;
}

void removeRec(Node *from, Node *to, int &s)
{
    typename std::vector<Node *>::iterator i = from->children.begin();
    bool exists = false;
    while (i != from->children.end())
    {
        exists = false;
        for (Node *chto : to->children)
            if ((*i)->val == chto->val)
            {
                removeRec(*i, chto, s);
                ++i;
                exists = true;
                break;
            }
        if (!exists)
            s += treeSum(*i++);
    }
}

void removeSubtrees(Node *&big, Node *small)
{
    if (isSubtreeFrom(big, small))
    {
        int sum = 0;
        removeRec(big, small, sum);
        big = new Node(sum);
    }
    else
    {
        for (Node *&ch : big->children)
            removeSubtrees(ch, small);
    }
}

void saveToFile(Node *root, const std::string &path)
{
    std::ofstream ofs(path);
    ofs << "| " << root->val << " |\n| ";
    std::queue<Node *> q;
    q.push(root);
    size_t lvlCnt = 1, nextCnt = 0;
    while (!q.empty())
    {
        root = q.front();
        q.pop();
        for (Node *ch : root->children)
        {
            ++nextCnt;
            q.push(ch);
            ofs << ch->val << ' ';
        }
        ofs << '|';
        if (lvlCnt == 1)
        {
            if (!q.empty())
                ofs << "\n|";
            lvlCnt = nextCnt;
            nextCnt = 0;
        }
        else
            --lvlCnt;
        ofs << ' ';
    }

    ofs.close();
}

int main()
{
    Node *r1 = readTree("tree1.t");
    Node *r2 = readTree("tree2.t");

    print(r1);
    std::cout << '\n';
    print(r2);
    std::cout << '\n';

    std::cout << std::boolalpha << isSubtree(r1, r2) << '\n';

    saveToFile(r2, "save2.t");

    removeSubtrees(r1, r2);
    print(r1);

    clear(r1);
    clear(r2);
    return 0;
}