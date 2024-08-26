#include "buffersubscription.h"


#include <csignal>
#include <QDebug>
#include <iostream>


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
    bool connectionSuccess = connect(&_buffer, &CircularBuffer::dataAdded, this, &BufferSubscription::onDataAddedToBuffer);
    if (!connectionSuccess) {
        qDebug() << "Failed to connect signal and slot for buffer:" << &_buffer;
    }

}
void BufferSubscription::registerSubscriber(QSharedPointer<I_Subscriber> subscriber, int lookBackPeriodMS, SensorDataType type)
{
    qDebug() << "Registering new subscriber for buffer " << &_buffer;
    _subscribers.push_back(subscriber);
    _lookBackPeriods.push_back(lookBackPeriodMS);
    _sensorDataTypes.push_back(type);  // Store the data type
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
            _sensorDataTypes.erase(_sensorDataTypes.begin() + i);
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
    // qDebug() << "Data added to buffer : " << &_buffer;
    for (size_t i = 0; i < _subscribers.size(); ++i) {
        try {
            // Ensure the lookback period is non-negative
            int lookBackPeriodMs = _lookBackPeriods.at(i);
            if (lookBackPeriodMs < 0) {
                throw std::invalid_argument("Lookback period cannot be negative.");
            }

            // Calculate the number of elements to read
            size_t elementsToRead = lookBackPeriodMs / dataIntervalsMS;

            // Ensure elementsToRead is within a valid range
            if (elementsToRead > _buffer.getBufferCapacity()) {
                throw std::out_of_range("Elements to read exceed the buffer size.");
            }

            // Read values from the buffer
            std::vector<double> values = _buffer.readLastNValues(elementsToRead);

            // Check if values vector is empty
            if (values.empty()) {
                throw std::runtime_error("Buffer returned an empty vector of values.");
            }

            // Pass the values to the subscriber
            if (_subscribers[i] != nullptr) {
                // qDebug() << "On New Data for " << &this->_buffer;
                _subscribers[i]->onNewData(values, _sensorDataTypes[i]);
            } else {
                throw std::runtime_error("Subscriber is null.");
            }
        } catch (const std::out_of_range& e) {
            // Handle out-of-range errors (e.g., accessing invalid indices or buffer overflow)
            std::cerr << "Out of range error: " << e.what() << " for subscriber index " << i << std::endl;
        } catch (const std::invalid_argument& e) {
            // Handle invalid argument errors (e.g., negative lookback period)
            std::cerr << "Invalid argument: " << e.what() << " for subscriber index " << i << std::endl;
        } catch (const std::runtime_error& e) {
            // Handle runtime errors (e.g., empty buffer, null subscriber)
            std::cerr << "Runtime error: " << e.what() << " for subscriber index " << i << std::endl;
        } catch (const std::exception& e) {
            // Catch any other standard exceptions
            std::cerr << "Exception: " << e.what() << " for subscriber index " << i << std::endl;
        } catch (...) {
            // Catch any other non-standard exceptions
            std::cerr << "Unknown error occurred for subscriber index " << i << std::endl;
        }
    }
}


