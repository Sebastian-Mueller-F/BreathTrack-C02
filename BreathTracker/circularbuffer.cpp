#include "circularbuffer.h"
#include <QDebug>

//TODO: Create Buffer Subscriber Class

template <typename T>
CircularBuffer<T>::CircularBuffer( size_t capacity, int newDataIntervalMS, QObject *parent) :
    _buffer(capacity),
    _newDataIntervalMS(newDataIntervalMS),
    _start(0),
    _end(0),
    _capacity(capacity),
    _size(0)
{

}


template<typename T>
void CircularBuffer<T>::writeNewItem(const T &newItem)
{
    //edge case ?

    //add new item to end pointer
    _buffer[_end] = newItem;
    //move end pointer
    _end = (_end + 1) % _capacity;

    if (_size < _capacity){
        //increase size until it matches capacity
        _size++;
    }
    else {
        //when size matches capacity move _start (to match end)
        _start = (_start +1) % _capacity;
    }

    emit dataAdded(_newDataIntervalMS);
}

template<typename T>
std::vector<T> CircularBuffer<T>::readLastNValues(size_t n)
{
    std::vector<T> values;
    size_t reader = (_end + _capacity - n) % _capacity;


    if (isEmpty()){
        return values;
    }

    // If N number of items is not available just return all items available ( = size)
    if (_size < n){
        qWarning() << " Only " << _size << " number of items in the buffer available. Will read and return " << _size << " values.";
        n = _size;
    }

    reader = _end;

    for (int i = 0; i < n; i++){

        //add to values
        values.push_back(_buffer[reader]);

        //move reader pointer
        reader = (reader + 1) % _capacity;
    }

    return values;
}

template<typename T>
bool CircularBuffer<T>::isEmpty()
{
    std::lock_guard<std::mutex> lock(_mtx);
    return _size == 0;
}

template<typename T>
bool CircularBuffer<T>::isFull()
{
    std::lock_guard<std::mutex> lock(_mtx);
    return _size == _capacity;
}

template<typename T>
size_t CircularBuffer<T>::getBufferSize()
{
     std::lock_guard<std::mutex> lock(_mtx);
    return _size;
}

template<typename T>
size_t CircularBuffer<T>::getBufferCapacity()
{
    std::lock_guard<std::mutex> lock(_mtx);
    return _capacity;
}



