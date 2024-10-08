#ifndef TRENDDATAAPI_H
#define TRENDDATAAPI_H

#include <QObject>
#include <QQmlEngine>
#include <QSharedPointer>
#include <QVariantList>

#include <databuffermanager.h>
#include <i_frontendapimodule.h>
#include <i_subscriber.h>
#include <types.h>

/**
 * @brief The TrendDataAPI class
 */

class TrendDataAPI : public QObject, public I_Subscriber, public I_FrontendAPIModule
{
    Q_OBJECT

    Q_PROPERTY(QVariantList raw READ raw WRITE setRaw NOTIFY rawChanged)
    Q_PROPERTY(QVariantList sma READ sma WRITE setSma NOTIFY smaChanged)
    Q_PROPERTY(QVariantList ema READ ema WRITE setEma NOTIFY emaChanged)

public:
    explicit TrendDataAPI(DataBufferManager *dataBufferManager = nullptr, QObject *parent = nullptr);

    ~TrendDataAPI() override;

    static TrendDataAPI *instance(DataBufferManager *dataBufferManager = nullptr,
                                  QObject *parent = nullptr);
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    void initialize(); // Method to set up subscriptions

    QVariantList raw() const;
    void setRaw(const QVariantList &newRaw);

    QVariantList sma() const;
    void setSma(const QVariantList &newSma);

    QVariantList ema() const;
    void setEma(const QVariantList &newEma);

signals:
  void rawChanged(QVariantList &newData);
  void smaChanged(QVariantList &newData);
  void emaChanged(QVariantList &newData);

private:
    static QScopedPointer<TrendDataAPI> _instance;

    DataBufferManager *_dataBufferManager;

    QVariantList _raw;
    QVariantList _sma;
    QVariantList _ema;

    // FrontendAPI
    void getBackendData() override;
    void handleFrontendRequest() override;
    void saveSettings(QString key, QVariant val) override;
    void loadSettings() override;

    // Subscriber
    void onNewData(const std::vector<double> &data, SensorDataType type) override;
};

#endif // TRENDDATAAPI_H
