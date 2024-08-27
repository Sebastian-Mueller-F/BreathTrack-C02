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
    explicit DataBufferManager(QObject *parent = nullptr);

    static std::shared_ptr<DataBufferManager> instance();

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

    static std::shared_ptr<DataBufferManager> _instance;

    size_t _rawCapacity = 1000;     // Example: 10 minutes at 1-second intervals
    size_t _averageCapacity = 1000; // Example: 5 minutes at 5-second intervals
    std::unordered_map<SensorDataType, CircularBuffer *> _buffers;
    std::unordered_map<SensorDataType, std::shared_ptr<BufferSubscription>> _subscriptions;

    // development functions
    void printBufferValues();
};

#endif // DATABUFFERMANAGER_H
