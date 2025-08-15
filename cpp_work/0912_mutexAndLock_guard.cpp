#include <ios>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx;
int g_number = 0;

void increaseNum(int count)
{
    std::lock_guard<std::mutex> lock(mtx);
    for (size_t i = 0; i < count; i++)
    {
        ++g_number;
    }
}

int main() {
    const int threadNums = 5;
    const int iterNums = 1000;
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 5; i++)
    {
        threads.emplace_back(increaseNum, iterNums);
    }
    
    for (auto &thread : threads) {
        thread.join();
    }

    std::cout << "g_number: " << g_number << std::endl;
    return 0;
}