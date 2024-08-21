#include "buffersubscription.h"


#include <csignal>


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
void BufferSubscription::registerSubscriber(QSharedPointer<Subscriber> subscriber, int lookBackPeriodMS)
{
    _subscribers.push_back(subscriber);
    _lookBackPeriods.push_back(lookBackPeriodMS);
}
void BufferSubscription::unregisterSubscriber(QSharedPointer<Subscriber> subscriber)
{
    bool success = false;

    for (int i = 0; i < _subscribers.size(); ++i) {
        if (_subscribers[i] == subscriber) {
            _subscribers.erase(_subscribers.begin() + i);
            _lookBackPeriods.erase(_lookBackPeriods.begin() + i);
            success = true;
            break;  // Exit the loop after removing the subscriber
        }
    }

    if (!success){
        throw SubscriberNotFoundException();
    }

}
void BufferSubscription::onDataAddedToBuffer(int dataIntervalsMS)
{
    for (size_t i = 0; i < _subscribers.size(); ++i) {
        int lookBackPeriodMs = _lookBackPeriods[i];
        size_t elementsToRead = lookBackPeriodMs / dataIntervalsMS;
        std::vector<double> values = _buffer.readLastNValues(elementsToRead);
        emit notifySubscribers(_subscribers[i], values);
    }
}

