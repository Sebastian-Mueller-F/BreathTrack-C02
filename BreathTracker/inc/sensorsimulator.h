#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include "I_Sensor.h"
#include <QObject>
#include <QTimer>

class SensorSimulator : public I_Sensor {
  Q_OBJECT
public:
  explicit SensorSimulator(double baseline = 55.0, double amplitude = 20.0,
                           int interval = 1000, QObject *parent = nullptr);

  static std::shared_ptr<SensorSimulator> instance();

  void startMeasurement() override;
  void stopMeasurement() override;
  SensorDataType sensorDataType() const override;

  ~SensorSimulator() override; // Destruktor hinzugefügt

  private slots:
  void generateNewCo2Value();

private:
    static std::shared_ptr<SensorSimulator> _instance;

    SensorDataType _sensorDataType = SensorDataType::RAW;
    QScopedPointer<QTimer> _timer;
    double _baseline;
    double _amplitude;
    int _interval;
};

#endif // SENSORSIMULATOR_H
