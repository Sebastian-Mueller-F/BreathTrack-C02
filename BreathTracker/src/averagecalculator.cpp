#include "averagecalculator.h"
#include <QDebug>
#include "buffersubscription.h"
#include "emaaverager.h"
#include "smaaverager.h"

AverageCalculator::AverageCalculator(std::shared_ptr<I_Sensor> sensor,
                                     size_t bufferSize,
                                     QObject *parent)
    : QObject(parent) // Make sure QObject is initialized properly
    , _sensor(sensor)
    , _buffer(std::make_unique<CircularBuffer>(bufferSize))
    , _subscription(new BufferSubscription(*_buffer))

{
    qDebug() << "AverageCalculator created with buffer size:" << bufferSize;
    initializeAveragers();
}

AverageCalculator::~AverageCalculator()
{
    qDebug() << "AverageCalculator destroyed";
    // Disconnect the signal-slot connection to avoid issues when this object is destroyed
    bool disconnected = QObject::disconnect(_sensor.get(), &I_Sensor::newCo2Value, this, nullptr);
    if (disconnected) {
        qDebug() << "Successfully disconnected sensor signal.";
    } else {
        qWarning() << "Failed to disconnect sensor signal!";
    }
}

void AverageCalculator::initializeAveragers()
{
    _smaAverager = SMAAverager::instance();
    _emaAverager = EMAAverager::instance();

    qDebug() << "Initializing averagers:";
    qDebug() << "SMAAverager instance:" << _smaAverager.get();
    qDebug() << "EMAAverger instance:" << _emaAverager.get();

    // Create in heap to manage life cycle

    _subscription->registerSubscriber(_smaAverager, 5000, SensorDataType::RAW);
    _subscription->registerSubscriber(_emaAverager, 10000, SensorDataType::RAW);

    qDebug() << "Registered SMA and EMA averagers to raw subscription.";
}

void AverageCalculator::start()
{
    qDebug() << "Starting AverageCalculator, connecting sensor signals...";
    bool receivingSensorDataSucess = QObject::connect(_sensor.get(),
                                                      &I_Sensor::newCo2Value,
                                                      this,
                                                      [&](double newCo2Value) {
                                                          onNewSensorData(newCo2Value);
                                                      });
    if (receivingSensorDataSucess) {
        qDebug() << "Successfully connected sensor signal.";
    } else {
        qCritical() << "Failed to connect signal to slot!";
    }
}

void AverageCalculator::onNewSensorData(double newCo2Value)
{
    qDebug() << "Received new sensor data:" << newCo2Value;
    if (_buffer) {
        _buffer->writeNewItem(newCo2Value);
        qDebug() << "New data written to raw buffer.";
    }
}
