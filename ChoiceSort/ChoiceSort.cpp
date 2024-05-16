#include <iostream>
#include <array>
#include <thread>
#include <future>
#include <utility>

const int ARR_SIZE = 6;

template<int SIZE>
void getIndMin(std::promise<int> pVal, std::array<int, SIZE>& arr, int start, int end)
{
    int min = arr[start];
    int indMin = start;
    for (int i = start + 1; i <= end; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            indMin = i;
        }
    }
    pVal.set_value(indMin);
}

template<int SIZE>
void choiceSort(std::array<int, SIZE>& arr, int start)
{
    int end = arr.size() - 1;
    if (start == end)
    {
        return;
    }
    std::promise<int> promVal;
    std::future<int> futVal{ promVal.get_future() };
    std::thread threadSearch(getIndMin<ARR_SIZE>, std::move(promVal), std::ref(arr), start, end);
    threadSearch.join();
    int indMin{ futVal.get() };
    std::swap(arr[start], arr[indMin]);
    choiceSort(arr, start + 1);
    return;
}

int main()
{
    std::array<int, ARR_SIZE> arr{ 4, 3, 7, 2, 1, 5 };
    choiceSort(arr, 0);
    std::cout << "Hi";
}
