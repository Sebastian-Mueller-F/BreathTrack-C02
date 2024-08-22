#include "databuffermanager.h"
#include <QDebug>

DataBufferManager::DataBufferManager(QObject *parent) : QObject(parent) {
    _buffers[SensorDataType::RAW] = new CircularBuffer(_rawCapacity);
    _buffers[SensorDataType::SMA] = new CircularBuffer(_averageCapacity);
    _buffers[SensorDataType::EMA] = new CircularBuffer(_averageCapacity);


    //data input for buffers
    connect(SensorSimulator::instance(), &SensorSimulator::newCo2Value, this, &DataBufferManager::onAverageUpdated);
    connect (EMAAverager::instance(), &EMAAverager::averageUpdated, this, &DataBufferManager::onAverageUpdated);
}

CircularBuffer *DataBufferManager::getBuffer(SensorDataType type)
{
    return _buffers[type];
}

void DataBufferManager::onAverageUpdated(double newAverage, SensorDataType averageType)
{
    qDebug()<<" On Average Updated" ;
}

