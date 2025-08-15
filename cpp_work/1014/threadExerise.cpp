#include <functional>
#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <chrono>
#include <utility>

int task(int num)
{
    std::cout << "thread Id: " << std::this_thread::get_id() << std::endl;
    return num * num;
}

void task1(int num, std::promise<int> &promise)
{
    promise.set_value(num * num);
}

int task2(std::shared_future<int> f)
{
    std::cout << "thread Id: " << std::this_thread::get_id() << std::endl;
    return f.get() + 10;
}

int main()
{
    // 1.
    // std::thread t(&task, 5);
    // t.join();

    // 2.
    auto res1 = std::async(std::launch::async, task, 5);
    // auto res2 = std::async(std::launch::deferred, task, 5);
    // std::cout << res1.get() << std::endl;
    auto shared_future = res1.share();

    std::thread t(task2, shared_future);
    auto res2 = std::async(std::launch::async, task2, shared_future);

    t.join();
    std::cout << res2.get() << std::endl;


    // 3.
    // std::promise<int> promise;
    // auto futures = promise.get_future();
    // std::thread t(task1, 5, std::ref(promise));
    // std::cout << futures.get() << std::endl;
    // t.join();
}