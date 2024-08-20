#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include <QObject>
#include <QTimer>

class SensorSimulator : public QObject
{
    Q_OBJECT
public:
    explicit SensorSimulator(double baseline = 50.0, double amplitude = 10.0, int interval = 1000, QObject *parent = nullptr );

signals:
    void newCo2Value(double value);

private slots:
    void generateSensorValuesInInterval(int interval);
    void generateNewCo2Value();

private :
    QScopedPointer<QTimer> _timer;
    double _baseline;
    double _amplitude;
    int _interval;


signals:
};

#endif // SENSORSIMULATOR_H
