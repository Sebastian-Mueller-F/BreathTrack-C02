#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <vector>

class Subscriber : public QObject {
    Q_OBJECT

public:
    explicit Subscriber(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~Subscriber() {}

    // Pure virtual function to be implemented by all subscribers
    virtual void onNewData(const std::vector<double>& data) = 0;
};

#endif // SUBSCRIBER_H
