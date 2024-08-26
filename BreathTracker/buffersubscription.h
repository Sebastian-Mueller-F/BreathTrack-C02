#ifndef BUFFERSUBSCRIPTION_H
#define BUFFERSUBSCRIPTION_H

#include <QObject>
#include <circularbuffer.h>
#include "I_Subscriber.h"
#include <types.h>

#include <QSharedPointer>


class BufferSubscription : public QObject {
    Q_OBJECT

public:
    BufferSubscription(CircularBuffer& buffer, QObject* parent = nullptr);

    void registerSubscriber(QSharedPointer<I_Subscriber> subscriber, int lookBackPeriodMS, SensorDataType dataType = SensorDataType::RAW);
    void unregisterSubscriber(QSharedPointer<I_Subscriber> subscriber);

private slots:
    void onDataAddedToBuffer(int dataIntervalsMS);

private:

    CircularBuffer& _buffer;
    QVector<QSharedPointer<I_Subscriber>> _subscribers;
    QVector<int> _lookBackPeriods;
    QVector<SensorDataType> _sensorDataTypes;

};

#endif // BUFFERSUBSCRIPTION_H
