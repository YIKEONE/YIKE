#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    virtual ~Observer() = default;

    virtual void update(double temperature, double humidity) = 0;
};

class TemperatureObserver : public Observer
{
public:
    void update(double temperature, double) override;
};

class HumidityObserver : public Observer
{
public:
    void update(double, double humidity) override;
};

#endif