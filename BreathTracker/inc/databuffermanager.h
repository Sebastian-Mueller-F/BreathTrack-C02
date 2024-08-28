#ifndef DATABUFFERMANAGER_H
#define DATABUFFERMANAGER_H

#include <QObject>

#include <buffersubscription.h>
#include <circularbuffer.h>
#include <emaaverager.h>
#include <sensorsimulator.h>
#include <smaaverager.h>
#include <types.h>

class DataBufferManager : public QObject
{
    Q_OBJECT
public:
    explicit DataBufferManager(std::shared_ptr<I_Sensor> sensor,
                               std::shared_ptr<I_Averager> smaAverager,
                               std::shared_ptr<I_Averager> emaAverager,
                               QObject *parent = nullptr);

    static std::shared_ptr<DataBufferManager> instance(std::shared_ptr<I_Sensor> sensor,
                                                       std::shared_ptr<I_Averager> smaAverager,
                                                       std::shared_ptr<I_Averager> emaAverager);

    CircularBuffer *getBuffer(SensorDataType type);

    void subscribe(std::shared_ptr<I_Subscriber> subscriber,
                   SensorDataType type,
                   int lookBackPeriodMS);
    void subscribeToAll(std::shared_ptr<I_Subscriber> subscriber, int lookBackPeriodMS);

private slots:
    void onNewData(double newData, SensorDataType sensorDataType);

signals:
    void bufferInitialized(SensorDataType type, CircularBuffer *buffer);

private:
    void initializeBuffers();
    void validateDependecies();

    static std::shared_ptr<DataBufferManager> _instance;

    std::shared_ptr<I_Sensor> _sensor;
    std::shared_ptr<I_Averager> _smaAverager;
    std::shared_ptr<I_Averager> _emaAverager;

    size_t _rawCapacity = 1000;     // Example: 10 minutes at 1-second intervals
    size_t _averageCapacity = 1000; // Example: 5 minutes at 5-second intervals
    std::unordered_map<SensorDataType, CircularBuffer *> _buffers;
    std::unordered_map<SensorDataType, std::shared_ptr<BufferSubscription>> _subscriptions;

    // development functions
    void printBufferValues();
};

#endif // DATABUFFERMANAGER_H
