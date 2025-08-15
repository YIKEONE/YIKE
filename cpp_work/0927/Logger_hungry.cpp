#include "Logger_hungry.h"
#include <iostream>
#include <memory>

std::shared_ptr<Logger_hungry> Logger_hungry::logger_ = std::shared_ptr<Logger_hungry>(new Logger_hungry());

Logger_hungry::Logger_hungry() {}

std::shared_ptr<Logger_hungry> Logger_hungry::getInstance()
{
    return logger_;
}

void Logger_hungry::log(const std::string &str)
{
    std::cout << str << std::endl;
}