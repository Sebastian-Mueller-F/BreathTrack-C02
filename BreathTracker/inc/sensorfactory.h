#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include <i_sensor.h>
#include <memory> // For std::shared_ptr
#include <sensorsimulator.h>

class SensorFactory
{
public:
    static std::shared_ptr<I_Sensor> createSensor(bool useSimulator)
    {
        if (useSimulator) {
            return SensorSimulator::instance();
        } else {
            // Replace with hardware sensor initialization when implemented
            // return std::make_shared<HardwareSensor>();
            throw std::logic_error("Hardware sensor initialization not implemented.");
        }
    }
};

#endif // SENSORFACTORY_H
