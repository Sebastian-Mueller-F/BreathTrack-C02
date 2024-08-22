#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <vector>

class Subscriber  {


public:
    //No constructor due to double inheritance, and no initialization needed here

    // virtual ~Subscriber() {}

    // Pure virtual function to be implemented by all subscribers
    virtual void onNewData(const std::vector<double>& data) = 0;
};

#endif // SUBSCRIBER_H
