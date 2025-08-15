/*练习目的：练习观察者模式
练习题目：设计一个气象站系统，该系统包含气象站（WeatherStation）和多个观察者（如TemperatureObserver和HumidityObserver），用于观察并响应气象站发布的气象信息（如温度和湿度）。气象站能够添加、删除观察者，并在气象数据更新时通知所有已注册的观察者。
要求：
实现观察者模式，包括 Subject（气象站）和 Observer（观察者）接口。
创建 WeatherStation 类作为 Subject 的具体实现，管理观察者的注册和注销，以及通知功能。
创建 TemperatureObserver 和 HumidityObserver 类作为 Observer 的具体实现，分别用于接收和响应温度和湿度的变化。
编写测试代码来演示气象站如何通知其观察者。*/

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <functional>
#include <vector>
#include <memory>
#include <set>

class Subject
{
protected:
    double temperature_;

    double humidity_;

    std::vector<std::shared_ptr<Observer>> observers_;
public:
    virtual ~Subject() = default;

    Subject(double temperature, double humidity) : temperature_(temperature), humidity_(humidity) {}

    virtual void registration(std::shared_ptr<Observer> observer) = 0;

    virtual void deregsitration(std::shared_ptr<Observer> observer) = 0;

    virtual void notify() const = 0;
};

class WeatherStation : Subject
{
public:
    WeatherStation(double temperature, double humidity);

    void registration(std::shared_ptr<Observer> observer) override;

    void deregsitration(std::shared_ptr<Observer> observer) override;

    void notify() const override;

};

class HumidityStation : public Subject
{
public:
    HumidityStation(double temperature, double humidity);

    void registration(std::shared_ptr<Observer> observer) override;

    void deregsitration(std::shared_ptr<Observer> observer) override;

    void notify() const override;
};

#endif