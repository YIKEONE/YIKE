#ifndef LOGGER_HUNGRY_H
#define LOGGER_HUNGRY_H

#include <string>
#include <memory>

class Logger_hungry
{
private:
    Logger_hungry();

    static std::shared_ptr<Logger_hungry> logger_;

    static std::shared_ptr<Logger_hungry> createInstance();
public:
    static std::shared_ptr<Logger_hungry> getInstance();

    void log(const std::string &str);
};

#endif