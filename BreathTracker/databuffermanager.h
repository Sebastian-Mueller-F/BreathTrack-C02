#ifndef DATABUFFERMANAGER_H
#define DATABUFFERMANAGER_H

#include <QObject>

#include <circularbuffer.h>
#include <types.h>


class DataBufferManager
{

public:
    DataBufferManager();

    //TODO: Include Buffer Subscription Class
    /* TODO: add data into buffers from..
     *      .. sensor
     *      .. sma
     *      .. ema
     */

    /* TODO: add subscribers to each buffer ..
     *      .. raw: Trend Calculator, FrontendAPI
     *      .. sma: Trend Calculator, FrontendAPI
     *      .. ema: Trend Calculator, FrontendAPI
     */



    CircularBuffer* getBuffer(SensorDataType type);

private:
    std::map<SensorDataType, CircularBuffer*> _buffers;
    size_t _rawCapacity = 600;   // Example: 10 minutes at 1-second intervals
    size_t _averageCapacity = 60; // Example: 5 minutes at 5-second intervals


};

#endif // DATABUFFERMANAGER_H
