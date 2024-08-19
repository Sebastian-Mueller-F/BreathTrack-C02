#include "sensorsimulator.h"
#include <QRandomGenerator>
#include <QDebug>

SensorSimulator::SensorSimulator(QObject *parent, double baseline, double amplitude )
    : QObject{parent},
    baseline(baseline),
    amplitude(amplitude)

{
    generateSensorValuesInInterval(1000);//generate sensor values every second

    //test readout created values
    connect(this, &SensorSimulator::newCo2Value, [&](double sensorValue) {
        qDebug() << " Sensor Co2 value : " << sensorValue;
    });
}

//Create function for starting the simulation

void SensorSimulator::generateSensorValuesInInterval(int interval)
{
    timer.reset(new QTimer(this));
    connect(timer.data(), &QTimer::timeout, this, &SensorSimulator::generateNewCo2Value);
    timer.data()->start(interval);
}

void SensorSimulator::generateNewCo2Value()
{
    //generate random value between -1.0 and + 1.0
    double random = QRandomGenerator::global()->generateDouble(); // val inbetween 0 and 1
    double transformedValue = 2.0 * random - 1.0; //val inbetween -1 and 1

    //simulated value
    double sensorValue = baseline + (transformedValue * amplitude);

    emit newCo2Value(sensorValue);

}

