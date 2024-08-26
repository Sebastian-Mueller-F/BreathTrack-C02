#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include <I_Sensor.h>
#include <sensorsimulator.h>


class SensorFactory
{
public:
    static I_Sensor* createSensor(bool useSimulator)
    {
        if (useSimulator) {
            return SensorSimulator::instance();
        } else {
            // Replace with hardware sensor initialization when implemented
            // return new HardwareSensor();
            return nullptr; // Placeholder until hardware sensor is available
        }
    }
};

#endif // SENSORFACTORY_H
