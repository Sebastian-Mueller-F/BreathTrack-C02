#include "sensorsimulator.h"
#include <QRandomGenerator>
#include <QDebug>

SensorSimulator* SensorSimulator::_instance = nullptr;

SensorSimulator::SensorSimulator( double baseline, double amplitude, int interval, QObject *parent)
    : QObject{parent},
    _baseline(baseline),
    _amplitude(amplitude),
    _interval(interval)

{
    generateSensorValuesInInterval(_interval);//generate sensor values every second

    //test readout created values
    connect(this, &SensorSimulator::newCo2Value, [&](double sensorValue) {
        qDebug() << " Sensor Co2 value : " << sensorValue;
    });
}

SensorSimulator *SensorSimulator::instance()
{
    if (_instance == nullptr){
        _instance = new SensorSimulator;
    }
    return _instance;
}

//Create function for starting the simulation

void SensorSimulator::generateSensorValuesInInterval(int interval)
{
    _timer.reset(new QTimer(this));
    connect(_timer.data(), &QTimer::timeout, this, &SensorSimulator::generateNewCo2Value);
    _timer.data()->start(interval);
}

void SensorSimulator::generateNewCo2Value()
{
    //generate random value between -1.0 and + 1.0
    double random = QRandomGenerator::global()->generateDouble(); // val inbetween 0 and 1
    double transformedValue = 2.0 * random - 1.0; //val inbetween -1 and 1

    //simulated value
    double sensorValue = _baseline + (transformedValue * _amplitude);

    emit newCo2Value(sensorValue, this->_sensorDataType);

}

