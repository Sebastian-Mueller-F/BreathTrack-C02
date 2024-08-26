#include "databuffermanager.h"
#include <QDebug>

std::shared_ptr<DataBufferManager> DataBufferManager::_instance = nullptr;

DataBufferManager::DataBufferManager(QObject *parent) : QObject(parent) {
    _buffers[SensorDataType::RAW] = new CircularBuffer(_rawCapacity);
    _buffers[SensorDataType::SMA] = new CircularBuffer(_averageCapacity);
    _buffers[SensorDataType::EMA] = new CircularBuffer(_averageCapacity);


    //data input for buffers
    connect(SensorSimulator::instance(), &SensorSimulator::newCo2Value, this, &DataBufferManager::onNewData);
    connect (EMAAverager::instance().data(), &EMAAverager::averageUpdated, this, &DataBufferManager::onNewData);

    //data output for subscribers
    QSharedPointer<TrendDataAPI> trendFrontend = TrendDataAPI::instance();
    BufferSubscription rawTrendBufferSubscription(*_buffers[SensorDataType::RAW]);
    BufferSubscription smaTrendBufferSubscription(*_buffers[SensorDataType::SMA]);
    BufferSubscription emaTrendBufferSubscription(*_buffers[SensorDataType::EMA]);

    //make trendAPI class a subscriber of the buffers
    //TODO: retrieve lookbackPeriod from Frontend
    rawTrendBufferSubscription.registerSubscriber(trendFrontend, 60000);
    smaTrendBufferSubscription.registerSubscriber(trendFrontend, 60000);
    emaTrendBufferSubscription.registerSubscriber(trendFrontend, 60000);

}

std::shared_ptr<DataBufferManager> DataBufferManager::instance()
{
    if (!_instance){
        _instance = std::shared_ptr<DataBufferManager>(new DataBufferManager);
    }
    return _instance;
}



CircularBuffer *DataBufferManager::getBuffer(SensorDataType type)
{
    return _buffers[type];
}

void DataBufferManager::onNewData(double newData, SensorDataType sensorDataType)
{
    qDebug()<<" New Data for Data Buffer from " << sensorDataType << ", data: " << newData;
    _buffers[sensorDataType]->writeNewItem(newData);

}

