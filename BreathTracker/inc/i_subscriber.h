#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <types.h>
#include <vector>

class I_Subscriber {

public:
    // No constructor or destructor due to double inheritance, and no initialization needed here
    // virtual ~Subscriber() {}

    // Pure virtual function to be implemented by all subscribers
    virtual void onNewData(const std::vector<double> &data,
                           SensorDataType type = SensorDataType::RAW)
        = 0;
};

#endif // SUBSCRIBER_H
