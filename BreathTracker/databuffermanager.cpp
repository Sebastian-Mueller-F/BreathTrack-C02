#include "databuffermanager.h"
#include <QDebug>
#include <QTimer>
#include <QMutexLocker>

std::shared_ptr<DataBufferManager> DataBufferManager::_instance = nullptr;

DataBufferManager::DataBufferManager(QObject *parent) : QObject(parent)
{

    initializeBuffers();
    //
    _rawTrendBufferSubscription = std::make_shared<BufferSubscription>(*_buffers[SensorDataType::RAW]);
    _smaTrendBufferSubscription = std::make_shared<BufferSubscription>(*_buffers[SensorDataType::SMA]);
    _emaTrendBufferSubscription = std::make_shared<BufferSubscription>(*_buffers[SensorDataType::EMA]);

    //data input for buffers
    connect(SensorSimulator::instance(), &SensorSimulator::newCo2Value, this, &DataBufferManager::onNewData);
    connect (SMAAverager::instance().data(), &SMAAverager::averageUpdated, this, &DataBufferManager::onNewData);
    connect (EMAAverager::instance().data(), &EMAAverager::averageUpdated, this, &DataBufferManager::onNewData);

    //data output for subscribers
    QSharedPointer<TrendDataAPI> trendFrontend = TrendDataAPI::instance();
    //make trendAPI class a subscriber of the buffers
    //TODO: retrieve lookbackPeriod from Frontend
    _rawTrendBufferSubscription->registerSubscriber(trendFrontend, 50000, SensorDataType::RAW);
    _smaTrendBufferSubscription->registerSubscriber(trendFrontend, 50000, SensorDataType::SMA);
    _emaTrendBufferSubscription->registerSubscriber(trendFrontend, 50000, SensorDataType::EMA);


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
    // qDebug()<<" New Data for Data Buffer from " << sensorDataType << ", data: " << newData;
    _buffers[sensorDataType]->writeNewItem(newData);

}

void DataBufferManager::initializeBuffers()
{
    _buffers[SensorDataType::RAW] = new CircularBuffer(_rawCapacity, 1000);
    _buffers[SensorDataType::SMA] = new CircularBuffer(_averageCapacity, 1000);
    _buffers[SensorDataType::EMA] = new CircularBuffer(_averageCapacity, 1000);

    // Ensure all buffers are initialized correctly
    if (!_buffers[SensorDataType::RAW] || !_buffers[SensorDataType::SMA] || !_buffers[SensorDataType::EMA]) {
        qDebug() << "Error: One or more buffers are not initialized correctly!";
    }
}

void DataBufferManager::printBufferValues()
{
    // RAW buffer values
            std::vector<double> rawValues = _buffers[SensorDataType::RAW]->readLastNValues(100);
    qDebug() << "RAW Buffer Values:";
    for (const double &value : rawValues) {
        qDebug() << value;
    }

    // SMA buffer values
    std::vector<double> smaValues = _buffers[SensorDataType::SMA]->readLastNValues(100);
    qDebug() << "SMA Buffer Values:";
    for (const double &value : smaValues) {
        qDebug() << value;
    }

    // EMA buffer values
    std::vector<double> emaValues = _buffers[SensorDataType::EMA]->readLastNValues(100);
    qDebug() << "EMA Buffer Values:";
    for (const double &value : emaValues) {
        qDebug() << value;
    }
}

