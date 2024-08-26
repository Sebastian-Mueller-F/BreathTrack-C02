#include "sensorsimulator.h"
#include <QRandomGenerator>
#include <QDebug>

SensorSimulator* SensorSimulator::_instance = nullptr;

SensorSimulator::SensorSimulator(double baseline, double amplitude, int interval, QObject *parent)
    : QObject(parent),  // Initialize QObject
    _baseline(baseline),
    _amplitude(amplitude),
    _interval(interval)
{
    _timer.reset(new QTimer(this));

    // Connect timer to the generateNewCo2Value slot
    connect(_timer.data(), &QTimer::timeout, this, &SensorSimulator::generateNewCo2Value);

    // Example debug output connection
    connect(this, &SensorSimulator::newCo2Value, [&](double sensorValue, SensorDataType type) {
        // qDebug() << "Sensor Co2 value: " << sensorValue;
    });
}

SensorSimulator* SensorSimulator::instance()
{
    if (_instance == nullptr) {
        _instance = new SensorSimulator;
    }
    return _instance;
}

void SensorSimulator::startMeasurement()
{
    if (!_timer->isActive()) {
        _timer->start(_interval);
        qDebug() << "Sensor Sim measurement started.";
    }
}

void SensorSimulator::stopMeasurement()
{
    if (_timer->isActive()) {
        _timer->stop();
        qDebug() << "Sensor Sim measurement stopped.";
    }
}

SensorDataType SensorSimulator::sensorDataType() const
{
    return _sensorDataType;
}

void SensorSimulator::generateNewCo2Value()
{
    double random = QRandomGenerator::global()->generateDouble(); // Value between 0 and 1
    double transformedValue = 2.0 * random - 1.0; // Value between -1 and 1

    double sensorValue = _baseline + (transformedValue * _amplitude);

    emit newCo2Value(sensorValue, _sensorDataType);
}
