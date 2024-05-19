#include <iostream>
#include <vector>
#include <future>

int blockCount = 4;


void parallForEach(std::vector<int> vec, std::vector<int>::iterator beg, std::vector<int>::iterator end)
{
    int size = vec.size();
    if (size < blockCount)
    {
        std::for_each(vec.cbegin(), vec.cend(), [](auto& val)
            {
                std::cout << val << " ";
            });
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    else
    {
        std::vector<int> vec1;
        std::vector<int> vec2;
        int endNew = (size % 2 != 0) ? size / 2 + 1 : size / 2;

        for (auto i = 0; i < endNew; ++i)
        {
            vec1.push_back(vec.at(i));
        }
        for (auto i = endNew; i < size; ++i)
        {
            vec2.push_back(vec.at(i));
        }
        std::async(std::launch::async, parallForEach, vec1, vec1.begin(), vec1.end());
        parallForEach(vec2, vec2.begin(), vec2.end());
    }
}


int main()
{
    std::vector<int> smallVec{ 1, 2, 3 };
    std::vector<int> bigVec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    parallForEach(smallVec, smallVec.begin(), smallVec.end());
    std::cout << std::endl;
    parallForEach(bigVec, bigVec.begin(), bigVec.end());
    std::cout << std::endl;
}