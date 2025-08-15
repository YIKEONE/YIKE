#include "Observer.h"
#include <iostream>

void TemperatureObserver::update(double temperature, double)
{
    std::cout << "current temperature: " << temperature << std::endl;
}

void HumidityObserver::update(double, double humidity)
{
    std::cout << "current humidity: " << humidity << std::endl;
}