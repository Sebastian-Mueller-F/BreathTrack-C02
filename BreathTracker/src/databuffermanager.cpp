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

DataBufferManager::~DataBufferManager()
{
    // Log the destruction for debugging
    qDebug() << "Destroying DataBufferManager Singleton instance.";

    // Disconnect all connected signals to this instance
    bool disconnected = disconnect(_sensor.get(),
                                   &SensorSimulator::newCo2ValueGenerated,
                                   this,
                                   &DataBufferManager::onNewData);
    if (!disconnected) {
        qWarning() << "Failed to disconnect sensor signal in DataBufferManager!";
    }
    disconnected = disconnect(_smaAverager.get(),
                              &SMAAverager::averageUpdated,
                              this,
                              &DataBufferManager::onNewData);
    if (!disconnected) {
        qWarning() << "Failed to disconnect SMAAverager signal in DataBufferManager!";
    }
    disconnected = disconnect(_emaAverager.get(),
                              &EMAAverager::averageUpdated,
                              this,
                              &DataBufferManager::onNewData);
    if (!disconnected) {
        qWarning() << "Failed to disconnect EMAAverager signal in DataBufferManager!";
    }

    // Delete dynamically allocated buffers before destroying them in heap automatically
    for (auto &[type, buffer] : _buffers) {
        if (buffer) {
            delete buffer;
            buffer = nullptr;
            qDebug() << "Buffer for" << type << "destroyed.";
        }
    }

    // Clear the subscriptions map to release all shared_ptr instances
    _subscriptions.clear();
    qDebug() << "All subscriptions cleared.";

    // Reset the singleton instance
    _instance.reset();
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

void DataBufferManager::unsubscribeFromAll(std::shared_ptr<I_Subscriber> subscriber)
{
    for (auto &[type, subscription] : _subscriptions) {
        if (subscription) {
            subscription->unregisterSubscriber(subscriber);
            qDebug() << "Unsubscribed" << subscriber.get() << "from buffer" << type;
        }
    }
}

void DataBufferManager::onNewData(double newData, SensorDataType sensorDataType)
{
    _buffers[sensorDataType]->writeNewItem(newData);
}

void DataBufferManager::initializeBuffers()
{
    //third argument make this the parent which automatically deleted the _buffers as they are QObjects
    _buffers[SensorDataType::RAW] = new CircularBuffer(_rawCapacity, 1000, this);
    _buffers[SensorDataType::SMA] = new CircularBuffer(_averageCapacity, 1000, this);
    _buffers[SensorDataType::EMA] = new CircularBuffer(_averageCapacity, 1000, this);

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
