#ifndef LIVEDATAAPI_H
#define LIVEDATAAPI_H

#include <QObject>
#include <QQmlEngine>

#include <I_Subscriber.h>
#include <I_FrontendAPI.h>
#include <FrontendTypes.h>
#include <sensorsimulator.h>
#include <smaaverager.h>
#include <emaaverager.h>



//Singleton
class LiveDataAPI : public QObject, public I_FrontendAPI
{
    Q_OBJECT
public:
    LiveDataAPI(QObject *parent = nullptr);

    ~LiveDataAPI() override {
        // Destructor
    }

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    //TODO: Change to std::unique / std::shared ?
    static LiveDataAPI *instance();

private:
    static LiveDataAPI *_instance;

    int _sensorValue;
    int _averagedValue;
    FrontendTypes::AverageType _averageType;

    Q_PROPERTY(int sensorValue READ sensorValue WRITE setSensorValue NOTIFY sensorValueChanged)
    Q_PROPERTY(int averagedValue READ averagedValue WRITE setAveragedValue NOTIFY averagedValueChanged )
    Q_PROPERTY(FrontendTypes::AverageType averageType READ averageType WRITE setAverageType NOTIFY averageTypeChanged )

    void getBackendData() override;
    void handleFrontendRequest() override;

    void saveSettings(QString key, QVariant val) override;
    void loadSettings() override;


public:
    int sensorValue() const;
    void setSensorValue(int newSensorValue);

    int averagedValue() const;
    void setAveragedValue(int newAveragedValue);

    FrontendTypes::AverageType averageType() const;
    void setAverageType(const FrontendTypes::AverageType &newAverageType);

signals:

    void sensorValueChanged();
    void averagedValueChanged();

    void averageTypeChanged();
};

#endif // LIVEDATAAPI_H
