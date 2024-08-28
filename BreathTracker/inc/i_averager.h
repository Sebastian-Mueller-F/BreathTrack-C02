#ifndef I_AVERAGER_H
#define I_AVERAGER_H

#include <QObject>

#include <types.h>

// Averager Interface

// TODO: I_ as Interface prefix
class I_Averager : public QObject {
  Q_OBJECT

public:
  explicit I_Averager(QObject *parent = nullptr) : QObject(parent) {}
  virtual ~I_Averager() {}

  // calculate the average
  virtual double calculate() = 0;

  // a method to get and set the period (number of data points)
  virtual size_t getPeriod() const = 0;
  virtual void setPeriod(size_t period) = 0;

  // Method to adjust internal data structures or state when the period changes
  virtual void onPeriodChanged() = 0;

  SensorDataType _averageType;

signals:
  void averageUpdated(double newAverage, SensorDataType averageType);
};

#endif // I_AVERAGER_H
