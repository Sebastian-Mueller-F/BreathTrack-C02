#ifndef ISENSOR_H
#define ISENSOR_H

#include <QObject>
#include <types.h>

class I_Sensor : public QObject {
  Q_OBJECT
public:
  explicit I_Sensor(QObject *parent = nullptr) : QObject(parent) {}

  virtual ~I_Sensor() = default;

  virtual void startMeasurement() = 0;
  virtual void stopMeasurement() = 0;
  virtual SensorDataType sensorDataType() const = 0;

signals:
    void newCo2ValueGenerated(double value, SensorDataType type);
};

#endif // ISENSOR_H
