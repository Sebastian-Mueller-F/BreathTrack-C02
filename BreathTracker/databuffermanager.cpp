#include "databuffermanager.h"

DataBufferManager::DataBufferManager() {
    buffers[RAW] = new CircularBuffer(rawCapacity);
    buffers[SMA] = new CircularBuffer(averageCapacity);
    buffers[EMA] = new CircularBuffer(averageCapacity);
}

CircularBuffer *DataBufferManager::getBuffer(BufferType type)
{
    return buffers[type];
}

