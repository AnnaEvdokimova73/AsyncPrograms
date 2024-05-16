#include <iostream>
#include <vector>
#include <future>

int blockCount = 4;

void printBlockPart(std::vector<int>::iterator beg, std::vector<int>::iterator end)
{
    for (auto it = beg; it < end; ++it)
    {
        std::cout << *it << " ";
    }
}

void forEach(std::vector<int> vec, int beg, int end)
{
    std::vector<int> vec1;
    std::vector<int> vec2;
    int endNew = (end % 2 != 0) ? end / 2 + 1 : end / 2;

    if (vec.size() == 1 || vec.size() == 2 || vec.size() == 3)
    {
        std::async(std::launch::async, printBlockPart, vec.begin(), vec.end());
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return;
    }
    for (auto i = 0; i < endNew; ++i)
    {
        vec1.push_back(vec.at(i));
    }
    for (auto i = endNew; i < end; ++i)
    {
        vec2.push_back(vec.at(i));
    }
    forEach(vec1, beg, endNew);
    forEach(vec2, endNew, vec2.size());

    //std::async(std::launch::async, printBlockPart, vec1.begin(), vec1.end());
    //std::async(std::launch::async, printBlockPart, vec2.begin(), vec2.end());

    return;
}

int main()
{
    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    forEach(vec, 0, vec.size());
}