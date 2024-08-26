#include "circularbuffer.h"
#include <QDebug>

//TODO: Create Buffer Subscriber Class


CircularBuffer::CircularBuffer( size_t capacity, int newDataIntervalMS, QObject *parent) :
    _buffer(capacity),
    _newDataIntervalMS(newDataIntervalMS),
    _start(0),
    _end(0),
    _capacity(capacity),
    _size(0)
{

}

CircularBuffer::~CircularBuffer()
{

}

void CircularBuffer::writeNewItem(const double &newItem)
{
    //edge case ?

    //add new item to end pointer
    _buffer[_end] = newItem;

    //move end pointer
    _end = (_end + 1) % _capacity;

    if (_size < _capacity) {
        //increase size until it matches capacity
        _size++;
    }
    else {
        //when size matches capacity move _start (to match end)
        _start = (_start + 1) % _capacity;
    }

    emit dataAdded(_newDataIntervalMS);
    qDebug() << "dataAdded signal emitted with interval:" << _newDataIntervalMS;
}


std::vector<double> CircularBuffer::readLastNValues(size_t n)
{
    std::vector<double> values;
    size_t reader = (_end + _capacity - n) % _capacity;


    if (isEmpty()){
        return values;
    }

    // If N number of items is not available just return all items available ( = size)
    if (_size < n){
        qWarning() << " Only " << _size << " number of items in the buffer available. Will read and return " << _size << " values.";
        n = _size;
    }

    for (int i = 0; i < n; i++){

        //add to values
        values.push_back(_buffer[reader]);

        //move reader pointer
        reader = (reader + 1) % _capacity;
    }

    return values;
}

std::vector<double> CircularBuffer::readAllValues()
{

    std::vector<double> values;
    if (isEmpty()) {
        return values;  // Return an empty vector if the buffer is empty
    }

    size_t reader = _start;  // Start reading from the oldest element
    for (size_t i = 0; i < _size; i++) {
        values.push_back(_buffer[reader]);  // Add the value to the result vector
        reader = (reader + 1) % _capacity;  // Move the reader pointer to the next element
    }

    return values;


}


bool CircularBuffer::isEmpty()
{
    std::lock_guard<std::mutex> lock(_mtx);
    return _size == 0;
}


bool CircularBuffer::isFull()
{
    std::lock_guard<std::mutex> lock(_mtx);
    return _size == _capacity;
}


size_t CircularBuffer::getBufferSize()
{
     std::lock_guard<std::mutex> lock(_mtx);
    return _size;
}


size_t CircularBuffer::getBufferCapacity()
{
    std::lock_guard<std::mutex> lock(_mtx);
    return _capacity;
}



