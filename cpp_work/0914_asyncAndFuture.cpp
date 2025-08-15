#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <fstream>


int main()
{
    auto future = std::async(std::launch::async, [](int x) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return x * x;
    }, 10);
    int res = future.get();
    std::cout << "res is: " << res << std::endl;

    std::ofstream outFile("0914_asyncAndFuture.txt");

    if (outFile.is_open())
    {
        outFile << "res is: " << res << std::endl;
        outFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return 0;
}