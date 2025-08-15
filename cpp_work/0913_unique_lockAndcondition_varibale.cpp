#include <chrono>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>

std::condition_variable g_cv;
std::mutex g_mtx;
std::queue<int> g_queue;
const int CAPACITY = 5;

void producer()
{
    for (size_t i = 0; i < 10; i++)
    {
        std::unique_lock<std::mutex> lock(g_mtx);
        while (g_queue.size() >= CAPACITY)
        {
            g_cv.wait(lock);
        }
        g_queue.emplace(1);
        std::cout << "Produced, cur capacity is: " << g_queue.size() << std::endl;
        g_cv.notify_one();
    }
}

void consumer()
{
    for (size_t i = 0; i < 10; ++i)
    {
        std::unique_lock<std::mutex> lock(g_mtx);
        while (g_queue.empty())
        {
            g_cv.wait(lock);
        }
        g_queue.pop();
        std::cout << "Consumed, cur capacity is: " << g_queue.size() << std::endl;
        g_cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}