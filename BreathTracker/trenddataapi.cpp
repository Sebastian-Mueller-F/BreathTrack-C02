#include "trenddataapi.h"

QSharedPointer<TrendDataAPI> TrendDataAPI::_instance = nullptr;

TrendDataAPI::TrendDataAPI(QObject *parent)
{
    // qRegisterMetaType<QList<double>>("QList<double>");
    qDebug() << "Test";
}

QSharedPointer<TrendDataAPI> TrendDataAPI::instance()
{
    if (_instance.isNull()) {
        _instance = QSharedPointer<TrendDataAPI>::create();
    }
    return _instance;
}

QVariantList TrendDataAPI::raw() const
{
    return _raw;
}

void TrendDataAPI::setRaw(const QVariantList &newRaw)
{
    if (_raw == newRaw)
        return;
    _raw = newRaw;
    emit rawChanged(_raw);
}

QVariantList TrendDataAPI::sma() const
{
    return _sma;
}

void TrendDataAPI::setSma(const QVariantList &newSma)
{
    if (_sma == newSma)
        return;
    _sma = newSma;
    emit smaChanged(_sma);
}

QVariantList TrendDataAPI::ema() const
{
    return _ema;
}

void TrendDataAPI::setEma(const QVariantList &newEma)
{
    if (_ema == newEma)
        return;
    _ema = newEma;
    emit emaChanged(_ema);
}

void TrendDataAPI::getBackendData()
{
        qDebug() << "Test";
}

void TrendDataAPI::handleFrontendRequest()
{
    qDebug() << "Test";
}

void TrendDataAPI::saveSettings(QString key, QVariant val)
{
    qDebug() << "Test";
}

void TrendDataAPI::loadSettings()
{
        qDebug() << "Test";
}

void TrendDataAPI::onNewData(const std::vector<double> &data, SensorDataType type)
{
    //T
    QVariantList newData;
    for (double value : data) {
        newData.append(value);
    }

    switch (type) {
    case SensorDataType::RAW:
        setRaw(newData); // Assuming the first value is used for RAW
        break;
    case SensorDataType::SMA:
        setSma(newData);
        break;
    case SensorDataType::EMA:
        // setEma(newData);
        break;
    default:
        qWarning() << "Unknown sensor data type received!";
        break;
    }
}

