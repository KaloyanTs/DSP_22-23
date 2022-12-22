#include <iostream>
#include <queue>

struct Node;
unsigned getHeight(Node *);
struct Node
{
    int data;
    Node *left, *right;
    unsigned height;
    Node(int _d, Node *l = nullptr, Node *r = nullptr, int h = 0) : data(_d),
                                                                    left(l),
                                                                    right(r),
                                                                    height(std::max(getHeight(l), getHeight(r)) + 1) {}

    void insert(int d)
    {
        if (d <= data)
        {
            if (left)
                left->insert(d);
            else
                left = new Node(d);
        }
        else
        {
            if (right)
                right->insert(d);
            else
                right = new Node(d);
        }
    }
};

unsigned getBalance(Node *root)
{
    if (!root)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

unsigned getHeight(Node *root)
{
    if (!root)
        return 0;
    return root->height;
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
    std::cout << '(' << root->data;
    if (root->left || root->right)
    {
        std::cout << ' ';
        print(root->left);
        std::cout << ' ';
        print(root->right);
    }
    std::cout << ')';
}

void rotateRight(Node *&root)
{
    Node *l = root->left;
    Node *lr = l->right;
    l->right = root;
    root->left = lr;
    root = l;
}

void rotateLeft(Node *&root)
{
    Node *r = root->right;
    Node *rl = r->left;
    r->left = root;
    root->right = rl;
    root = r;
}

void rotateLeftSpecial(Node *&root)
{
    rotateRight(root->right);
    rotateLeft(root);
}

void rotateRightSpecial(Node *&root)
{
    rotateLeft(root->left);
    rotateRight(root);
}

int main()
{
    Node *r = new Node(5);
    r->insert(2);
    r->insert(4);
    r->insert(1);
    r->insert(7);
    r->insert(6);
    r->insert(9);
    print(r);
    rotateRight(r);
    rotateLeft(r);
    std::cout << '\n';
    print(r);

    clear(r);
    return 0;
}