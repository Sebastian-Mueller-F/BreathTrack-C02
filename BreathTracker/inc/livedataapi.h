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
class LiveDataAPI : public QObject, public I_FrontendAPI {
  Q_OBJECT
public:
  LiveDataAPI(QObject *parent = nullptr);

  ~LiveDataAPI() override;

  static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
  // TODO: Change to std::unique / std::shared ?
  static LiveDataAPI *instance();

private:
    static QScopedPointer<LiveDataAPI> _instance;

    int _smaPeriod;
    int _emaPeriod;
    int _sensorValue;
    int _averagedValue;
    FrontendTypes::AverageType _averageType;

    Q_PROPERTY(int smaPeriod READ smaPeriod WRITE setSmaPeriod NOTIFY smaPeriodChanged FINAL)
    Q_PROPERTY(int emaPeriod READ emaPeriod WRITE setEmaPeriod NOTIFY emaPeriodChanged FINAL)
    Q_PROPERTY(int sensorValue READ sensorValue WRITE setSensorValue NOTIFY sensorValueChanged)
    Q_PROPERTY(
        int averagedValue READ averagedValue WRITE setAveragedValue NOTIFY averagedValueChanged)
    Q_PROPERTY(FrontendTypes::AverageType averageType READ averageType WRITE setAverageType NOTIFY
                   averageTypeChanged)

    void getBackendData() override;
    void handleFrontendRequest() override;
    void saveSettings(QString key, QVariant val) override;
    void loadSettings() override;

    void updatePeriodInAveragers();

public:
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

signals:

  void sensorValueChanged();
  void averagedValueChanged();

  void averageTypeChanged();
  void averagingPeriodChanged();
  void smaPeriodChanged();
  void emaPeriodChanged();
};

#endif // LIVEDATAAPI_H
