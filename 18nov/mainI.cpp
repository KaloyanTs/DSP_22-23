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
        Tab *tmp = head;
        while (head)
        {
            head = head->pNext;
            delete tmp;
            tmp = head;
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
        head = new Tab(url, head);
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
    Browser() : current(new Window(DEFAULT_TAB_URL)), wCount(1), timestamp(time(0)) {}
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
    bool operate(const std::string &url)
    {
        Tab *ptr = current->head;
        while (ptr && ptr->url != url)
            ptr = ptr->pNext;
        if (!ptr)
        {
            current->openTab(url);
            current->showTabs();
            return true;
        }
        Tab *cleaner = current->head;
        while (current->head != ptr)
        {
            current->head = current->head->pNext;
            delete cleaner;
            cleaner = current->head;
        }
        current->showTabs();
        return false;
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
                if (openWindow())
                    std::cout << "New window opened!\n";
                else
                    throw std::logic_error("Something went wrong...");
            }
            else if (!strcmp(cmnd, "-C"))
            {
                if (closeWindow())
                    std::cout << "Current window closed!\n";
                else
                    throw std::logic_error("Something went wrong...");
            }
        }
        else if (!strcmp(cmnd, "TAB"))
        {
            std::cin >> cmnd;
            if (operate(cmnd))
                std::cout << "Append!\n";
            else
                std::cout << "Trim!\n";
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
    try
    {
        do
        {
            // chrome.showWindows();
            std::cin >> cmnd;
        } while (chrome.command(cmnd));
    }
    catch (const std::exception &err)
    {
        std::cout<<err.what();
    }

    return 0;
}