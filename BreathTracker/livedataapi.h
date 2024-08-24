#ifndef LIVEDATAAPI_H
#define LIVEDATAAPI_H

#include <QObject>
#include <QQmlEngine>

#include <I_Subscriber.h>
#include <I_FrontendAPI.h>
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
    int _averageType;  //TODO: Make enum

    Q_PROPERTY(int sensorValue READ sensorValue WRITE setSensorValue NOTIFY sensorValueChanged)
    Q_PROPERTY(int averagedValue READ averagedValue WRITE setAveragedValue NOTIFY averagedValueChanged FINAL)

    void getBackendData() override;
    void handleFrontendRequest() override;

    void saveSettings(QString key, QVariant val) override;
    void loadSettings() override;


public:
    int sensorValue() const;
    void setSensorValue(int newSensorValue);

    int averagedValue() const;
    void setAveragedValue(int newAveragedValue);

signals:

    void sensorValueChanged();
    void averagedValueChanged();


};

#endif // LIVEDATAAPI_H
