#ifndef LIVEDATAAPI_H
#define LIVEDATAAPI_H

#include <QObject>
#include <I_Subscriber.h>

class LiveDataAPI : public QObject, public I_Subscriber
{
Q_OBJECT
public:
    LiveDataAPI();

private:

    double _sensorValue;
    double _averagedValue;

    Q_PROPERTY(double sensorValue READ sensorValue WRITE setSensorValue NOTIFY sensorValueChanged)
    Q_PROPERTY(double averagedValue READ averagedValue WRITE setAveragedValue NOTIFY averagedValueChanged FINAL)

public:
    double sensorValue() const;
    void setSensorValue(double newSensorValue);

    double averagedValue() const;
    void setAveragedValue(double newAveragedValue);

signals:

    void sensorValueChanged();
    void averagedValueChanged();


};

#endif // LIVEDATAAPI_H
