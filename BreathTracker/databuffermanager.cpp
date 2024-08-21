#include "databuffermanager.h"

DataBufferManager::DataBufferManager() {
    _buffers[RAW] = new CircularBuffer(_rawCapacity);
    _buffers[SMA] = new CircularBuffer(_averageCapacity);
    _buffers[EMA] = new CircularBuffer(_averageCapacity);
}

CircularBuffer *DataBufferManager::getBuffer(SensorDataType type)
{
    return _buffers[type];
}

