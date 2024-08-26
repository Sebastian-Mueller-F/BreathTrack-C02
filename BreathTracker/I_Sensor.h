#ifndef I_SENSOR_H
#define I_SENSOR_H

// #include <functional>
#include <types.h>

class I_Sensor
{
public:
    virtual ~I_Sensor() = default;

    // Start and stop measurement functions
    virtual void startMeasurement() = 0;
    virtual void stopMeasurement() = 0;

    // Return the type of sensor data
    virtual SensorDataType sensorDataType() const = 0;

    // Allow setting a callback for when new CO2 values are available
    // virtual void setNewCo2ValueCallback(std::function<void(double, SensorDataType)> callback) = 0;
};

#endif // I_SENSOR_H
