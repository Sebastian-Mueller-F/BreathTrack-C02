#ifndef AVERAGER_H
#define AVERAGER_H

#include <QObject>

// Averager Interface
class Averager : public QObject {
    Q_OBJECT

public:
    explicit Averager(QObject *parent = nullptr) : QObject(parent) {}

    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~Averager() {}

    // Pure virtual function to calculate the average
    virtual double calculate() = 0;

    // Optionally, a method to get and set the period (number of data points)
    virtual size_t getPeriod() const = 0;
    virtual void setPeriod(size_t period) = 0;

signals:
    // Signal to notify when a new average is calculated
    void averageUpdated(double newAverage);
};

#endif // AVERAGER_H
