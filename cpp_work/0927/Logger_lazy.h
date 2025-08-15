#ifndef LOGGER_LAZY_H
#define LOGGER_LAZY_H

#include <memory>
#include <mutex>
#include <string>

class Logger_lazy
{
private:
    Logger_lazy();

    Logger_lazy(const Logger_lazy &) = delete;

    Logger_lazy operator=(const Logger_lazy&) = delete;

    static std::once_flag initInstanceFlag;

    static std::shared_ptr<Logger_lazy> logger_;
public:
    static std::shared_ptr<Logger_lazy> getInstance();

    void log(const std::string &str);
};

#endif