#include "Observer.h"
#include "WeatherStation.h"
#include <memory>

int main()
{
    WeatherStation ws(20, 0.5);
    HumidityStation hs(30, 0.6);

    auto tempObs = std::make_shared<TemperatureObserver>();
    auto humiObs = std::make_shared<HumidityObserver>();

    ws.deregsitration(humiObs);
    ws.registration(tempObs);
    ws.registration(humiObs);
    ws.notify();

    hs.deregsitration(humiObs);
    hs.registration(tempObs);
    hs.registration(humiObs);
    hs.notify();

}