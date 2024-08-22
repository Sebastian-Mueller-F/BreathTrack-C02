#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <vector>

class Subscriber  {


public:
    explicit Subscriber();
    virtual ~Subscriber() {}

    // Pure virtual function to be implemented by all subscribers
    virtual void onNewData(const std::vector<double>& data) = 0;
};

#endif // SUBSCRIBER_H
