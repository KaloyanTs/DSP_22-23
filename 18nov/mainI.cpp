#include <iostream>
#include <string>
#include <cstring>
#include <ctime>

const unsigned WINDOW_LIMIT = 255;
const std::string DEFAULT_TAB_URL = "http://exam_dsa";
const unsigned INPUT_MAX = 127;

struct Tab
{
    std::string url;
    time_t timestamp;
    Tab *pNext;
    Tab(const std::string &_url, Tab *_p = nullptr)
        : url(_url), timestamp(time(0)), pNext(_p) {}
    Tab(const Tab &other) = delete;
    Tab &operator=(const Tab &other) = delete;
    void printTab() const
    {
        std::cout << "\t\t{url:\t" << url << '\t' << timestamp << '}';
    }
};

struct Window
{
    Tab *head;
    Window *pNext;
    Window *pPrev;
    time_t oldestTab;
    Window(const std::string &url, Window *prev = nullptr, Window *next = nullptr)
        : head(new Tab(url)), pNext(next), pPrev(prev), oldestTab(head->timestamp) {}
    ~Window()
    {
        if (!head)
            return;
        Tab *tmp = head->pNext;
        while (tmp)
        {
            head->pNext = tmp->pNext;
            delete tmp;
            tmp = head->pNext;
        }
    }
    Window(const Window &other) = delete;
    Window &operator=(const Window &other) = delete;
    bool isActive() { return head; }
    void clearTabs()
    {
        Tab *tmp = head;
        while (head)
        {
            head = head->pNext;
            delete tmp;
            tmp = head;
        }
    }
    void openTab(const std::string &url)
    {
        Tab *tmp = head;
        while (tmp->pNext)
            tmp = tmp->pNext;
        tmp->pNext = new Tab(url);
    }
    unsigned tabCount()
    {
        unsigned res = 0;
        Tab *tmp = head;
        while (tmp)
        {
            ++res;
            tmp = tmp->pNext;
        }
        return res;
    }
    void showTabs()
    {
        std::cout << "\tTabs:\n";
        Tab *tmp = head;
        while (tmp)
        {
            tmp->printTab();
            std::cout << '\n';
            tmp = tmp->pNext;
        }
    }
};

struct Browser
{
    Window *current;
    size_t wCount;
    time_t timestamp;
    Browser() : current(new Window(DEFAULT_TAB_URL)), wCount(0), timestamp(time(0)) {}
    Browser(const Browser &other) = delete;
    Browser &operator=(const Browser &other) = delete;
    ~Browser()
    {
        unsigned closedTabs = 0;
        if (!current)
            return;
        Window *tmp = current;
        while (current->pPrev)
        {
            tmp = current->pPrev;
            current->pPrev = tmp->pPrev;
            closedTabs += tmp->tabCount();
            delete tmp;
        }
        while (current->pNext)
        {
            tmp = current->pNext;
            current->pNext = tmp->pNext;
            closedTabs += tmp->tabCount();
            delete tmp;
        }
        closedTabs += current->tabCount();
        delete current;
        std::cout << "Total closed tabs: " << closedTabs
                  << '\n'
                  << "Total time of usage: " << time(0) - timestamp
                  << '\n';
    }
    bool openWindow()
    {
        if (wCount >= WINDOW_LIMIT)
            return false;
        if (!current)
            current = new Window(DEFAULT_TAB_URL);
        else
        {
            current->pNext = new Window(DEFAULT_TAB_URL, current, current->pNext);
            current = current->pNext;
            if (current->pNext)
                current->pNext->pPrev = current;
        }
        ++wCount;
        return true;
    }
    bool closeWindow()
    {
        if (!current)
            return false;
        current->clearTabs();
        Window *tmp = current->pNext, *tmpPrev = current->pPrev;
        if (!tmp && !tmpPrev)
        {
            delete current;
            current = nullptr;
            --wCount;
        }
        else if (!tmp)
        {
            current = current->pPrev;
            delete current->pNext;
            current->pNext = nullptr;
        }
        else if (!tmpPrev)
        {
            current = current->pNext;
            delete current->pPrev;
            current->pPrev = nullptr;
        }
        else
        {
            tmpPrev->pNext = tmp;
            tmp->pPrev = tmpPrev;
            delete current;
            current = tmp->pPrev;
        }
        --wCount;
        return true;
    }
    time_t uptime()
    {
        if (!current)
            throw std::runtime_error("no windows");
        return time(0) - current->oldestTab;
    }
    void operate(const std::string &url)
    {
        Tab *p = current->head;
        Tab *nextP = p;
        while (p && p->url != url)
            p = p->pNext;
        if (!p)
        {
            current->openTab(url);
            std::cout << "Append\n";
            return;
        }
        do
        {
            nextP = p->pNext;
            while (nextP && nextP->url != url)
                nextP = nextP->pNext;
        } while (nextP);

        nextP = current->head;
        time_t newOldest = nextP->timestamp;
        while (nextP != p->pNext)
        {
            if (newOldest > nextP->timestamp)
                newOldest = nextP->timestamp;
            nextP = nextP->pNext;
        }
        current->oldestTab = newOldest;

        nextP = p;
        p = p->pNext;
        while (p)
        {
            nextP->pNext = p->pNext;
            delete p;
            p = nextP->pNext;
        }
        std::cout << "Trim\n";
    }
    bool command(char *cmnd)
    {
        if (!strcmp(cmnd, "EXIT"))
            return false;
        if (!strcmp(cmnd, "WINDOW"))
        {
            std::cin >> cmnd;
            if (!strcmp(cmnd, "-O"))
            {
                openWindow();
                std::cout << "New window opened!\n";
            }
            else if (!strcmp(cmnd, "-C"))
            {
                closeWindow();
                std::cout << "Current window closed!\n";
            }
        }
        else if (!strcmp(cmnd, "TAB"))
        {
            std::cin >> cmnd;
            operate(cmnd);
        }
        else if (!strcmp(cmnd, "UPTIME"))
            std::cout << uptime() << '\n';
        return true;
    }
    void showWindows() const
    {
        std::cout << "Windows:\n";
        if (!current)
            return;
        Window *begin = current;
        while (begin->pPrev)
            begin = begin->pPrev;
        while (begin)
        {
            begin->showTabs();
            if (begin == current)
                std::cout << "\t^active\n";
            begin = begin->pNext;
        }
    }
};

int main()
{
    Browser chrome;
    std::cout << "Browser started.\n";
    char cmnd[INPUT_MAX + 1];
    do
    {
        chrome.showWindows();
        std::cin >> cmnd;
    } while (chrome.command(cmnd));

    return 0;
}