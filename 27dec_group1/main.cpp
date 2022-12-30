#include <iostream>
#include <queue>

struct Node
{
    int value;
    Node *left, *right;
    Node(int _value, Node *_left = nullptr, Node *_right = nullptr)
        : value(_value), left(_left), right(_right) {}
    bool isLeaf() const { return !left && !right; }
};

void print(const Node *root)
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
    std::cout << root->value << ' ';
    print(root->left);
    std::cout << ' ';
    print(root->right);
    std::cout << ')';
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

void tryAdding(const Node *buf, size_t &next, std::queue<const Node *> &q)
{
    if (buf)
    {
        ++next;
        q.push(buf);
    }
}

int equalLevel(const Node *t1, const Node *t2)
{
    if (t1->value == t2->value)
        return 0;
    size_t level = 1;
    size_t levelCount1 = 0, levelCount2 = 0;
    size_t nextLevelCount1, nextLevelCount2;
    const Node *buf1, *buf2;
    std::queue<const Node *> q1, q2;
    tryAdding(t1->left, levelCount1, q1);
    tryAdding(t1->right, levelCount1, q1);
    tryAdding(t2->left, levelCount2, q2);
    tryAdding(t2->right, levelCount2, q2);
    while (!q1.empty() && !q2.empty())
    {
        nextLevelCount1 = nextLevelCount2 = 0;
        if (levelCount1 != levelCount2)
        {
            while (levelCount1)
            {
                buf1 = q1.front();
                q1.pop();
                --levelCount1;
                tryAdding(buf1->left, nextLevelCount1, q1);
                tryAdding(buf1->right, nextLevelCount1, q1);
            }
            while (levelCount2)
            {
                buf2 = q2.front();
                q2.pop();
                --levelCount2;
                tryAdding(buf2->left, nextLevelCount2, q2);
                tryAdding(buf2->right, nextLevelCount2, q2);
            }
            ++level;
            levelCount1 = nextLevelCount1;
            levelCount2 = nextLevelCount2;
            nextLevelCount1 = nextLevelCount2 = 0;
        }
        else
        {
            while (levelCount1)
            {
                buf1 = q1.front();
                q1.pop();
                buf2 = q2.front();
                q2.pop();
                --levelCount1;
                --levelCount2;
                tryAdding(buf1->left, nextLevelCount1, q1);
                tryAdding(buf1->right, nextLevelCount1, q1);
                tryAdding(buf2->left, nextLevelCount2, q2);
                tryAdding(buf2->right, nextLevelCount2, q2);
                if (buf1->value != buf2->value)
                {
                    while (levelCount1)
                    {
                        buf1 = q1.front();
                        q1.pop();
                        --levelCount1;
                        buf2 = q2.front();
                        q2.pop();
                        tryAdding(buf1->left, nextLevelCount1, q1);
                        tryAdding(buf1->right, nextLevelCount1, q1);
                        tryAdding(buf2->left, nextLevelCount2, q2);
                        tryAdding(buf2->right, nextLevelCount2, q2);
                    }
                    ++level;
                    levelCount1 = nextLevelCount1;
                    levelCount2 = nextLevelCount2;
                    nextLevelCount1 = nextLevelCount2 = 0;
                    continue;
                }
            }
            if (!levelCount1)
                return level;
        }
        ++level;
    }
    return -1;
}

void insert(Node *&root, int val)
{
    if (!root)
    {
        root = new Node(val);
        return;
    }
    if (val <= root->value)
        insert(root->left, val);
    else
        insert(root->right, val);
}

int removeEvens(Node *&root)
{
    if (!root)
        return 0;
    int lRes = removeEvens(root->left);
    int rRes = removeEvens(root->right);
    if (root->value % 2)
        return lRes + rRes;
    int res = root->value + lRes + rRes;
    if (root->isLeaf() && root->value % 2 == 0)
    {
        delete root;
        root = nullptr;
        return res;
    }
    Node *tmp = root->left;
    if (!tmp)
    {
        tmp = root->right;
        if (!tmp->left)
        {
            tmp->left = root->left;
            delete root;
            root = tmp;
            return res;
        }
        Node *par = tmp;
        tmp = tmp->left;
        while (tmp->left)
        {
            par = par->left;
            tmp = tmp->left;
        }
        par->left = nullptr;
        tmp->left = root->left;
        tmp->right = root->right;
        delete root;
        root = tmp;
        return res;
    }
    if (!tmp->right)
    {
        tmp->right = root->right;
        delete root;
        root = tmp;
        return res;
    }
    Node *par = tmp;
    tmp = tmp->right;
    while (tmp->right)
    {
        par = par->right;
        tmp = tmp->right;
    }
    par->right = nullptr;
    tmp->right = root->right;
    tmp->left = root->left;
    delete root;
    root = tmp;
    return res;
}

void exchangeEvens(Node *&root)
{
    if (!root || root->isLeaf())
        return;
    insert(root, removeEvens(root));
}

int main()
{
    Node *t1 = new Node(5,
                        new Node(3,
                                 new Node(4),
                                 new Node(3)),
                        new Node(2,
                                 new Node(3)));
    Node *t2 = new Node(6, new Node(7, new Node(4), new Node(3)), new Node(2, nullptr, new Node(3)));
    print(t1);
    std::cout << '\n';
    print(t2);
    std::cout << '\n';
    std::cout << equalLevel(t1, t2) << '\n';
    clear(t1);
    clear(t2);

    insert(t1, 6);
    insert(t1, 1);
    insert(t1, 7);
    insert(t1, 4);
    insert(t1, 11);
    insert(t1, 5);
    insert(t1, -6);
    insert(t1, 8);
    insert(t1, 13);
    insert(t1, 10);
    insert(t1, -16);
    insert(t1, 2);
    print(t1);
    std::cout << '\n';
    exchangeEvens(t1);
    print(t1);
    std::cout << '\n';

    return 0;
}