#include "livedataapi.h"

LiveDataAPI::LiveDataAPI() {}

double LiveDataAPI::sensorValue() const
{
    return _sensorValue;
}

void LiveDataAPI::setSensorValue(double newSensorValue)
{
    if (newSensorValue != _sensorValue){
        _sensorValue = newSensorValue;
    }

}

double LiveDataAPI::averagedValue() const
{
    return _averagedValue;
}
