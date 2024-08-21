#include "databuffermanager.h"

DataBufferManager::DataBufferManager() {
    _buffers[SensorDataType::RAW] = new CircularBuffer(_rawCapacity);
    _buffers[SensorDataType::SMA] = new CircularBuffer(_averageCapacity);
    _buffers[SensorDataType::EMA] = new CircularBuffer(_averageCapacity);
}

CircularBuffer *DataBufferManager::getBuffer(SensorDataType type)
{
    return _buffers[type];
}

