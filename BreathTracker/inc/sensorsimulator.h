#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include "i_sensor.h"
#include <QObject>
#include <QTimer>

class SensorSimulator : public I_Sensor {
  Q_OBJECT
public:
  explicit SensorSimulator(double baseline = 55.0, double amplitude = 20.0,
                           int interval = 1000, QObject *parent = nullptr);

  ~SensorSimulator() override; // Destruktor hinzugefügt

  static std::shared_ptr<SensorSimulator> instance();

  void startMeasurement() override;
  void stopMeasurement() override;
  SensorDataType sensorDataType() const override;

  private slots:
  void generateNewCo2Value();

private:
    static std::shared_ptr<SensorSimulator> _instance;

    QScopedPointer<QTimer> _timer;
    double _baseline;
    double _amplitude;
    int _interval;
    SensorDataType _sensorDataType;
};

#endif // SENSORSIMULATOR_H
