#include <iostream>

struct Node
{
    int data;
    Node *left, *right;
    Node(int d, Node *l = nullptr, Node *r = nullptr) : data(d), left(l), right(r) {}
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
        return;
    print(root->left);
    std::cout << root->data << ' ';
    print(root->right);
}

int main()
{
    Node *r = new Node(5);
    r->insert(4);
    r->insert(3);
    r->insert(2);
    r->insert(6);
    r->insert(9);
    r->insert(1);
    r->insert(3);
    print(r);

    clear(r);
    return 0;
}