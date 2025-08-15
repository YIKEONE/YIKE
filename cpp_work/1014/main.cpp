#include "sensitiveWordManager.h"

#include "dirent.h"
#include <string>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <thread>
#include <chrono>

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();

    SensitiveWordManager& instance = SensitiveWordManager::GetInstance();
    instance.AddSensitiveWord("tobbe");
    instance.AddSensitiveWord("regulus");
    instance.AddSensitiveWord("drven");
    instance.AddSensitiveWord("shark");
    instance.AddSensitiveWord("1");
    instance.AddSensitiveWord("2");
    instance.AddSensitiveWord("3");
    instance.AddSensitiveWord("4");
    instance.AddSensitiveWord("a4");
    instance.AddSensitiveWord("w4");
    instance.AddSensitiveWord("e4");
    instance.AddSensitiveWord("r4");
    bool status;
    std::string res;
    std::tie(status, res) = instance.CheckSensitiveWord("im 1234 tobbe 3 w4 r4 e3 a4 e4");
    std::cout << res << std::endl;

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = endTime -startTime;
    std::cout << "time: " << time.count() << " seconds\n";
}