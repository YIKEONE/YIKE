#include "Logger_lazy.h"
#include <memory>
#include <mutex>
#include <iostream>

std::once_flag Logger_lazy::initInstanceFlag;

std::shared_ptr<Logger_lazy> Logger_lazy::logger_;

std::shared_ptr<Logger_lazy> Logger_lazy::getInstance()
{
    std::call_once(initInstanceFlag, []() {
        Logger_lazy::logger_ = std::shared_ptr<Logger_lazy>(new Logger_lazy());
        // Logger_lazy::logger_.reset(new Logger_lazy());
    });
    return Logger_lazy::logger_;
}

void Logger_lazy::log(const std::string &str)
{
    std::cout << str << std::endl;
}

Logger_lazy::Logger_lazy() {}