#ifndef BUFFERSUBSCRIPTION_H
#define BUFFERSUBSCRIPTION_H

#include <QObject>
#include <circularbuffer.h>
#include <QSharedPointer>


class BufferSubscription : public QObject {
    Q_OBJECT

public:
    BufferSubscription(CircularBuffer& buffer, QObject* parent);


    void registerSubscriber(QSharedPointer<QObject> subscriber, int lookBackPeriodMS);
    void unregisterSubscriber(QSharedPointer<QObject> subscriber);

signals :
    void notifySubscribers(QSharedPointer<QObject> subscriber,const std::vector<double> values);

private slots:
    void onDataAddedToBuffer(int dataIntervalsMS);

private:

    CircularBuffer& _buffer;
    QVector<QSharedPointer<QObject>> _subscribers;
    QVector<int> _lookBackPeriods;

};

#endif // BUFFERSUBSCRIPTION_H
