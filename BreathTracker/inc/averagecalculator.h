#ifndef AVERAGECALCULATOR_H
#define AVERAGECALCULATOR_H

#include "CircularBuffer.h"
#include "I_Sensor.h"
#include "I_Subscriber.h"
#include <memory>

class AverageCalculator : public QObject
{
    Q_OBJECT
public:
    AverageCalculator(std::shared_ptr<I_Sensor> sensor,
                      size_t bufferSize,
                      QObject *parent = nullptr);
    ~AverageCalculator();

    void start();

private:
    std::unique_ptr<CircularBuffer> _buffer;
    std::shared_ptr<I_Sensor> _sensor;
    std::shared_ptr<I_Subscriber> _smaAverager;
    std::shared_ptr<I_Subscriber> _emaAverager;

    void initializeAveragers();
    void onNewSensorData(double newCo2Value);
};

#endif // AVERAGECALCULATOR_H
