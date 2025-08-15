#include <future>
#include <iostream>
#include <thread>
#include <utility>

int main()
{
    std::promise<int> promise;
    auto future = promise.get_future();

    std::thread t1([](std::promise<int> promise, int num) {
        promise.set_value(num * num);
    }, std::move(promise), 7);

    auto res = future.get();
    std::cout << "res: " << res << std::endl;

    if (t1.joinable())
    {
        t1.join();
    }
}