#include "buffersubscription.h"


#include <csignal>
#include <QDebug>


// maybe easier to add this directly to the buffer class!! ?!

class SubscriberNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Subscriber not found in BufferSubscription";
    }
};


BufferSubscription::BufferSubscription(CircularBuffer& buffer, QObject *parent)
:   QObject(parent),
    _buffer(buffer)
{
     //connect to buffer
    connect(&_buffer, &CircularBuffer::dataAdded, this, &BufferSubscription::onDataAddedToBuffer);
}
void BufferSubscription::registerSubscriber(QSharedPointer<I_Subscriber> subscriber, int lookBackPeriodMS)
{
    qDebug() << "Registering new subscriber with lookBackPeriodMS:" << lookBackPeriodMS;
    _subscribers.push_back(subscriber);
    _lookBackPeriods.push_back(lookBackPeriodMS);
    qDebug() << "Subscriber registered. Total subscribers:" << _subscribers.size();
}

void BufferSubscription::unregisterSubscriber(QSharedPointer<I_Subscriber> subscriber)
{
    qDebug() << "Attempting to unregister subscriber";
    bool success = false;

    for (int i = 0; i < _subscribers.size(); ++i) {
        if (_subscribers[i] == subscriber) {
            qDebug() << "Subscriber found. Removing subscriber at index:" << i;
            _subscribers.erase(_subscribers.begin() + i);
            _lookBackPeriods.erase(_lookBackPeriods.begin() + i);
            success = true;
            break;  // Exit the loop after removing the subscriber
        }
    }

    if (success) {
        qDebug() << "Subscriber successfully unregistered. Total subscribers:" << _subscribers.size();
    } else {
        qDebug() << "Subscriber not found. Throwing SubscriberNotFoundException.";
        throw SubscriberNotFoundException();
    }
}

void BufferSubscription::onDataAddedToBuffer(int dataIntervalsMS)
{
    for (size_t i = 0; i < _subscribers.size(); ++i) {
        int lookBackPeriodMs = _lookBackPeriods[i];
        size_t elementsToRead = lookBackPeriodMs / dataIntervalsMS;

        std::vector<double> values = _buffer.readLastNValues(elementsToRead);

        _subscribers[i]->onNewData(values);
    }
}

