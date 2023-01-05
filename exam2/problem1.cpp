#include <iostream>
#include <cstring>
#include <exception>
#include <vector>

template <typename T>
struct Node
{
    T data;
    Node<T> *left, *right;
    Node(const T &d, Node<T> *l = nullptr, Node<T> *r = nullptr) : data(d), left(l), right(r) {}
};

template <typename T>
void clear(Node<T> *&root)
{
    if (!root)
        return;
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

bool canRead(const Node<char> *root, const char *begin, const char *end)
{
    if (begin == end)
        return true;
    if (!root || root->data != *begin)
        return false;
    return canRead(root->left, begin + 1, end) || canRead(root->right, begin + 1, end);
}

bool readWord(const Node<char> *tree, const char *word)
{
    size_t l = strlen(word);
    if (strlen(word) < 4)
        throw std::logic_error("word is too short to be read from the tree...");
    if (!tree)
        return false;
    const char *end = word + l;
    const char *separate = word + 2;
    bool res = (canRead(tree->left, separate, end) && canRead(tree->right, word, separate));
    while (separate + 2 != end && !res)
    {
        ++separate;
        res = (canRead(tree->left, separate, end) && canRead(tree->right, word, separate));
    }
    return res;
}

size_t minLevel(const Node<char> *tree)
{
    using NodeContainer = std::vector<const Node<char> *>;
    NodeContainer v1, v2;
    NodeContainer *lvlNodes = &v1;
    NodeContainer *nextLvlNodes = &v2;
    bool lvlRes;
    size_t lvl = 1;
    typename NodeContainer::iterator i;
    if (tree->right)
        nextLvlNodes->push_back(tree->right);
    if (tree->left)
        nextLvlNodes->push_back(tree->left);
    while (!nextLvlNodes->empty())
    {
        ++lvl;
        std::swap(lvlNodes, nextLvlNodes);
        nextLvlNodes->clear();
        lvlRes = true;
        for (i = lvlNodes->begin(); (i + 1) != lvlNodes->end(); ++i)
        {
            lvlRes = lvlRes && (*i)->data <= (*(i + 1))->data;
            if ((*i)->right)
                nextLvlNodes->push_back((*i)->right);
            if ((*i)->left)
                nextLvlNodes->push_back((*i)->left);
        }
        if (lvlRes)
            return lvl;
        if ((*i)->right)
            nextLvlNodes->push_back((*i)->right);
        if ((*i)->left)
            nextLvlNodes->push_back((*i)->left);
    }
    return 0;
    // level not found
}

int main()
{
    Node<char> *t = new Node<char>('F',
                                   new Node<char>('B',
                                                  new Node<char>('A'),
                                                  new Node<char>('D',
                                                                 new Node<char>('C'),
                                                                 new Node<char>('E'))),
                                   new Node<char>('G',
                                                  nullptr,
                                                  new Node<char>('I',
                                                                 new Node<char>('H'))));

    try
    {
        std::cout << "GIBDC:\t" << std::boolalpha << readWord(t, "GIBDC") << '\n';
        std::cout << "GIBD:\t" << std::boolalpha << readWord(t, "GIBD") << '\n';
        std::cout << "GIBCD:\t" << std::boolalpha << readWord(t, "GIBCD") << '\n';
        std::cout << "GHBD:\t" << std::boolalpha << readWord(t, "GHBD") << '\n';
        std::cout << "GIBA:\t" << std::boolalpha << readWord(t, "GIBA") << '\n';
        std::cout << "GBA:\t" << std::boolalpha << readWord(t, "GBA") << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\nLevels are now\nF\nB\tG\nA\tD\tI\nC\tE\tH\n";
    std::cout << "Min level with characters in increasing order right to left: " << minLevel(t) << '\n';

    clear(t);

    t = new Node<char>('F',
                       new Node<char>('B',
                                      new Node<char>('I'),
                                      new Node<char>('D',
                                                     new Node<char>('C'),
                                                     new Node<char>('E'))),
                       new Node<char>('G',
                                      nullptr,
                                      new Node<char>('A',
                                                     new Node<char>('H'))));

    std::cout << "\nLevels are now\nF\nB\tG\nI\tD\tA\nC\tE\tH\n";
    std::cout << "Min level with characters in increasing order right to left: " << minLevel(t) << '\n';

    clear(t);

    return 0;
}