#include "sensitiveWordManager.h"

#include <future>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_set>
#include <vector>

SensitiveWordManager::SensitiveWordManager() = default;

SensitiveWordManager::~SensitiveWordManager() = default;

SensitiveWordManager& SensitiveWordManager::GetInstance()
{
    static SensitiveWordManager instance;
    return instance;
}

void SensitiveWordManager::AddSensitiveWord(const std::string& sensitive)
{
    std::lock_guard<std::mutex> lock(mutex_);
    sensitiveWords_.insert(sensitive);
}

void SensitiveWordManager::DeleteSensitiveWord(const std::string& word)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto count = sensitiveWords_.erase(word);
}

void SensitiveWordManager::ModifySensitiveWord(const std::string& before, const std::string& after)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = sensitiveWords_.find(before);
    if (it != sensitiveWords_.end())
    {
        sensitiveWords_.erase(it);
        sensitiveWords_.insert(after);
    }
}

std::string CheckAsync(const std::unordered_set<std::string> &sensitiveWords, const std::string &sentence,
    std::unordered_set<std::string>::const_iterator startIter, std::unordered_set<std::string>::const_iterator endIter)
{
    std::string res;
    for (; startIter != endIter; ++startIter)
    {
        if (sentence.find(*startIter) != std::string::npos)
        {
            res += " " + *startIter;
        }
    }
    return res;
}

std::tuple<bool, std::string> SensitiveWordManager::CheckSensitiveWord(const std::string& sentence) const
{
    const int num_threads = 4;
    int work_per_thread = sensitiveWords_.size() / num_threads;
    int remainde = sensitiveWords_.size() % num_threads;
    auto startIter = sensitiveWords_.begin();

    // deliver asyncWork, improve speed
    std::vector<std::future<std::string>> asyncWorks;
    for (size_t i = 0; i < num_threads; ++i)
    {
        auto endIter = startIter;
        std::advance(endIter, work_per_thread + ((i < remainde) ? 1 : 0));
        asyncWorks.emplace_back(
            std::async(std::launch::async, CheckAsync, 
                std::cref(sensitiveWords_), std::cref(sentence), startIter, endIter));
        startIter = endIter;
    }
    
    std::string res;
    for (auto &&asyncWork : asyncWorks)
    {
        res += asyncWork.get();
    }
    
    if (!res.empty())
    {   
        return { true, res };
    }
    return { false, "" };
}