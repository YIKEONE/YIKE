/*练习目的：练习观察者模式
练习题目：设计一个气象站系统，该系统包含气象站（WeatherStation）和多个观察者（如TemperatureObserver和HumidityObserver），
用于观察并响应气象站发布的气象信息（如温度和湿度）。气象站能够添加、删除观察者，并在气象数据更新时通知所有已注册的观察者。
要求：
实现观察者模式，包括 Subject（气象站）和 Observer（观察者）接口。
创建 WeatherStation 类作为 Subject 的具体实现，管理观察者的注册和注销，以及通知功能。
创建 TemperatureObserver 和 HumidityObserver 类作为 Observer 的具体实现，分别用于接收和响应温度和湿度的变化。
编写测试代码来演示气象站如何通知其观察者。*/

#include "WeatherStation.h"
#include <algorithm>
#include <iostream>

WeatherStation::WeatherStation(double temperature, double humidity) : Subject(temperature, humidity) {}

void WeatherStation::registration(std::shared_ptr<Observer> observer)
{
    observers_.emplace_back(observer);
}

void WeatherStation::deregsitration(std::shared_ptr<Observer> observer)
{
    auto it = std::remove(observers_.begin(), observers_.end(), observer);
    if (it == observers_.end())
    {
        std::cout << "The current observer is not registered\n";
        return;
    }
    observers_.erase(it, observers_.end());
}

void WeatherStation::notify() const
{
    for (auto &observer : observers_)
    {
        observer->update(temperature_, humidity_);
    }
}

HumidityStation::HumidityStation(double temperature, double humidity) : Subject(temperature, humidity) {}

void HumidityStation::registration(std::shared_ptr<Observer> observer)
{
    observers_.emplace_back(observer);
}

void HumidityStation::deregsitration(std::shared_ptr<Observer> observer)
{
    auto it = std::remove(observers_.begin(), observers_.end(), observer);
    if (it == observers_.end())
    {
        std::cout << "The current observer is not registered\n";
        return;
    }
    observers_.erase(it, observers_.end());
}

void HumidityStation::notify() const
{
    for (auto &&observer : observers_)
    {
        observer->update(temperature_, humidity_);
    }
}