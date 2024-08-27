#ifndef LIVEDATAAPI_H
#define LIVEDATAAPI_H

#include <QObject>
#include <QQmlEngine>
#include <QScopedPointer>

#include <FrontendTypes.h>
#include <I_FrontendAPI.h>
#include <I_Subscriber.h>
#include <emaaverager.h>
#include <sensorsimulator.h>
#include <smaaverager.h>

// Singleton
class LiveDataAPI : public QObject, public I_FrontendAPIModule
{
    Q_OBJECT
    Q_PROPERTY(int smaPeriod READ smaPeriod WRITE setSmaPeriod NOTIFY smaPeriodChanged FINAL)
    Q_PROPERTY(int emaPeriod READ emaPeriod WRITE setEmaPeriod NOTIFY emaPeriodChanged FINAL)
    Q_PROPERTY(int sensorValue READ sensorValue WRITE setSensorValue NOTIFY sensorValueChanged)
    Q_PROPERTY(
        int averagedValue READ averagedValue WRITE setAveragedValue NOTIFY averagedValueChanged)
    Q_PROPERTY(FrontendTypes::AverageType averageType READ averageType WRITE setAverageType NOTIFY
                   averageTypeChanged)

public:
    explicit LiveDataAPI(I_Sensor *sensorSimulator,
                         I_Averager *smaAverager,
                         I_Averager *emaAverager,

                         QObject *parent = nullptr);

    ~LiveDataAPI() override;

    void initialize();
    bool validateDependencies();

    int sensorValue() const;
    void setSensorValue(int newSensorValue);
    int averagedValue() const;
    void setAveragedValue(int newAveragedValue);

    FrontendTypes::AverageType averageType() const;
    void setAverageType(const FrontendTypes::AverageType &newAverageType);

    int smaPeriod() const;
    Q_INVOKABLE void setSmaPeriod(int newSmaPeriod);
    int emaPeriod() const;
    Q_INVOKABLE void setEmaPeriod(int newEmaPeriod);

private:
    int _smaPeriod;
    int _emaPeriod;
    int _sensorValue;
    int _averagedValue;
    FrontendTypes::AverageType _averageType;

    void getBackendData() override;
    void handleFrontendRequest() override;
    void saveSettings(QString key, QVariant val) override;
    void loadSettings() override;

    void updatePeriodInAveragers();

    I_Sensor *_sensor;
    I_Averager *_smaAverager;
    I_Averager *_emaAverager;

signals:

    void sensorValueChanged();
    void averagedValueChanged();

    void averageTypeChanged();
    void averagingPeriodChanged();
    void smaPeriodChanged();
    void emaPeriodChanged();
};

#endif // LIVEDATAAPI_H
