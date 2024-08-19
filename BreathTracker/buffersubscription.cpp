#include "buffersubscription.h"
#include <csignal>

// maybe easier to add this directly to the buffer class!!

class SubscriberNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Subscriber not found in BufferSubscription";
    }
};



template<typename T>
BufferSubscription<T>::BufferSubscription(CircularBuffer<T>& buffer, QObject *parent)
:   QObject(parent),
    _buffer(buffer)
{
     //connect to buffer
    connect(&_buffer, &CircularBuffer<T>::dataAdded, this, &BufferSubscription<T>::onDataAddedToBuffer);
}

template<typename T>
void BufferSubscription<T>::registerSubscriber(QSharedPointer<QObject> subscriber, int lookBackPeriodMS)
{
    _subscribers.push_back(subscriber);
    _lookBackPeriods.push_back(lookBackPeriodMS);
}

template<typename T>
void BufferSubscription<T>::unregisterSubscriber(QSharedPointer<QObject> subscriber)
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

template<typename T>
void BufferSubscription<T>::onDataAddedToBuffer(int dataIntervalsMS)
{
    for (size_t i = 0; i < _subscribers.size(); ++i) {
        int lookBackPeriodMs = _lookBackPeriods[i];
        size_t elementsToRead = lookBackPeriodMs / dataIntervalsMS;
        QVector<T> values = _buffer.readLastNValues(elementsToRead);
        emit notifySubscribers(_subscribers[i], values);
    }
}

