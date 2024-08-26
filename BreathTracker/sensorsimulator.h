#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include <QObject>
#include <QTimer>
#include "I_Sensor.h"

class SensorSimulator : public QObject, public I_Sensor
{
    Q_OBJECT
public:
    explicit SensorSimulator(double baseline = 55.0, double amplitude = 20.0, int interval = 1000, QObject *parent = nullptr);

    static SensorSimulator* instance();

    void startMeasurement() override;
    void stopMeasurement() override;
    SensorDataType sensorDataType() const override;

signals:
    void newCo2Value(double value, SensorDataType type);

private slots:
    void generateNewCo2Value();

private:
    static SensorSimulator* _instance;

    SensorDataType _sensorDataType = SensorDataType::RAW;
    QScopedPointer<QTimer> _timer;
    double _baseline;
    double _amplitude;
    int _interval;
};

#endif // SENSORSIMULATOR_H
