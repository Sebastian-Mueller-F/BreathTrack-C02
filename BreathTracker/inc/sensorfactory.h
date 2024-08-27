#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include <I_Sensor.h>
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
            return nullptr;
        }
    }
};

#endif // SENSORFACTORY_H
