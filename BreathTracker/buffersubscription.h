#ifndef BUFFERSUBSCRIPTION_H
#define BUFFERSUBSCRIPTION_H

#include <QObject>
#include <circularbuffer.h>
#include <QSharedPointer>

template <typename T>
class BufferSubscription : public QObject {
    Q_OBJECT

public:
    BufferSubscription(CircularBuffer<T>& buffer, QObject* parent);


    void registerSubscriber(QSharedPointer<QObject> subscriber, int lookBackPeriodMS);
    void unregisterSubscriber(QSharedPointer<QObject> subscriber);

signals :
    void notifySubscribers(QSharedPointer<QObject> subscriber,const QVector<T> values);

private slots:
    void onDataAddedToBuffer(int dataIntervalsMS);

private:

    CircularBuffer<T>& _buffer;
    QVector<QSharedPointer<QObject>> _subscribers;
    QVector<int> _lookBackPeriods;

};

#endif // BUFFERSUBSCRIPTION_H
