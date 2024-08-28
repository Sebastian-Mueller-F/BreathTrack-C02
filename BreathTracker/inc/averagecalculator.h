#ifndef AVERAGECALCULATOR_H
#define AVERAGECALCULATOR_H

#include "circularbuffer.h"
#include "i_sensor.h"
#include "i_subscriber.h"
#include <buffersubscription.h>
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
    std::unique_ptr<BufferSubscription> _subscription;
    std::shared_ptr<I_Subscriber> _smaAverager;
    std::shared_ptr<I_Subscriber> _emaAverager;

    void initializeAveragers();
    void onNewSensorData(double newCo2Value);
};

#endif // AVERAGECALCULATOR_H
