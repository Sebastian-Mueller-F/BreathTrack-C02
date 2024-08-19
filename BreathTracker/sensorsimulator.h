#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include <QObject>
#include <QTimer>

class SensorSimulator : public QObject
{
    Q_OBJECT
public:
    explicit SensorSimulator(QObject *parent = nullptr, double baseline = 50.0, double amplitude = 10.0 );

signals:
    void newCo2Value(double value);

private slots:
    void generateSensorValuesInInterval(int interval);
    void generateNewCo2Value();

private :
    QScopedPointer<QTimer> timer;
    double baseline;
    double amplitude;


signals:
};

#endif // SENSORSIMULATOR_H
