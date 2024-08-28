#include "databuffermanager.h"
#include <QDebug>

std::shared_ptr<DataBufferManager> DataBufferManager::_instance = nullptr;

DataBufferManager::DataBufferManager(std::shared_ptr<I_Sensor> sensor,
                                     std::shared_ptr<I_Averager> smaAverager,
                                     std::shared_ptr<I_Averager> emaAverager,
                                     QObject *parent)
    : _sensor(sensor)
    , _smaAverager(smaAverager)
    , _emaAverager(emaAverager)
    , QObject(parent)

{
    initializeBuffers();
    validateDependecies();

    // Connect data input sources to buffers
    connect(_sensor.get(), &SensorSimulator::newCo2ValueGenerated, this, &DataBufferManager::onNewData);
    connect(_smaAverager.get(), &SMAAverager::averageUpdated, this, &DataBufferManager::onNewData);
    connect(_emaAverager.get(), &EMAAverager::averageUpdated, this, &DataBufferManager::onNewData);
}

std::shared_ptr<DataBufferManager> DataBufferManager::instance(
    std::shared_ptr<I_Sensor> sensorSimulator,
    std::shared_ptr<I_Averager> smaAverager,
    std::shared_ptr<I_Averager> emaAverager)
{
    if (!_instance) {
        _instance = std::make_shared<DataBufferManager>(sensorSimulator, smaAverager, emaAverager);
        qDebug() << "DataBufferManager Singleton instance created.";
    }
    return _instance;
}

CircularBuffer *DataBufferManager::getBuffer(SensorDataType type)
{
    return _buffers[type];
}

void DataBufferManager::subscribe(std::shared_ptr<I_Subscriber> subscriber,
                                  SensorDataType type,
                                  int lookBackPeriodMS)
{
    if (_subscriptions.find(type) == _subscriptions.end()) {
        _subscriptions[type] = std::make_shared<BufferSubscription>(*_buffers[type]);
    }
    _subscriptions[type]->registerSubscriber(subscriber, lookBackPeriodMS, type);
}

void DataBufferManager::subscribeToAll(std::shared_ptr<I_Subscriber> subscriber,
                                       int lookBackPeriodMS)
{
    for (const auto &[type, buffer] : _buffers) {
        subscribe(subscriber, type, lookBackPeriodMS);
    }
}

void DataBufferManager::onNewData(double newData, SensorDataType sensorDataType)
{
    _buffers[sensorDataType]->writeNewItem(newData);
}

void DataBufferManager::initializeBuffers()
{
    _buffers[SensorDataType::RAW] = new CircularBuffer(_rawCapacity, 1000);
    _buffers[SensorDataType::SMA] = new CircularBuffer(_averageCapacity, 1000);
    _buffers[SensorDataType::EMA] = new CircularBuffer(_averageCapacity, 1000);

    // Ensure all buffers are initialized correctly
    if (!_buffers[SensorDataType::RAW] || !_buffers[SensorDataType::SMA]
        || !_buffers[SensorDataType::EMA]) {
        qDebug() << "Error: One or more buffers are not initialized correctly!";
    }
}

void DataBufferManager::validateDependecies()
{
    if (!_sensor) {
        qCritical() << "SensorSimulator instance is nullptr!";
    } else {
        qDebug() << "SensorSimulator instance is valid.";
    }

    if (!_smaAverager) {
        qCritical() << "SMAAverager instance is nullptr!";
    } else {
        qDebug() << "SMAAverager instance is valid.";
    }

    if (!_emaAverager) {
        qCritical() << "EMAAverager instance is nullptr!";
    } else {
        qDebug() << "EMAAverger instance is valid.";
    }
}

void DataBufferManager::printBufferValues()
{
    // Output buffer values
    std::vector<double> rawValues = _buffers[SensorDataType::RAW]->readLastNValues(100);
    qDebug() << "RAW Buffer Values:";
    for (const double &value : rawValues) {
        qDebug() << value;
    }

    std::vector<double> smaValues = _buffers[SensorDataType::SMA]->readLastNValues(100);
    qDebug() << "SMA Buffer Values:";
    for (const double &value : smaValues) {
        qDebug() << value;
    }

    std::vector<double> emaValues = _buffers[SensorDataType::EMA]->readLastNValues(100);
    qDebug() << "EMA Buffer Values:";
    for (const double &value : emaValues) {
        qDebug() << value;
    }
}
