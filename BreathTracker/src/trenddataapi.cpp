#include "trenddataapi.h"

QSharedPointer<TrendDataAPI> TrendDataAPI::_instance = nullptr;

TrendDataAPI::TrendDataAPI(QObject *parent) {
  // qRegisterMetaType<QList<double>>("QList<double>");
}

QObject *TrendDataAPI::qmlInstance(QQmlEngine *engine,
                                   QJSEngine *scriptEngine) {
  Q_UNUSED(scriptEngine)
  Q_UNUSED(engine)

  return TrendDataAPI::instance().data();
}

QSharedPointer<TrendDataAPI> TrendDataAPI::instance() {
  if (_instance.isNull()) {
    _instance = QSharedPointer<TrendDataAPI>::create();
  }
  return _instance;
}

QVariantList TrendDataAPI::raw() const { return _raw; }

void TrendDataAPI::setRaw(const QVariantList &newRaw) {
  if (_raw == newRaw)
    return;
  _raw = newRaw;
  emit rawChanged(_raw);
}

QVariantList TrendDataAPI::sma() const { return _sma; }

void TrendDataAPI::setSma(const QVariantList &newSma) {
  if (_sma == newSma)
    return;
  _sma = newSma;
  emit smaChanged(_sma);
}

QVariantList TrendDataAPI::ema() const { return _ema; }

void TrendDataAPI::setEma(const QVariantList &newEma) {
  if (_ema == newEma)
    return;
  _ema = newEma;
  emit emaChanged(_ema);
}

void TrendDataAPI::getBackendData() {}

void TrendDataAPI::handleFrontendRequest() {}

void TrendDataAPI::saveSettings(QString key, QVariant val) {}

void TrendDataAPI::loadSettings() {}

void TrendDataAPI::onNewData(const std::vector<double> &data,
                             SensorDataType type) {
  // qDebug() << "TrendDataAPI Data size received: " << data.size();
  QVariantList newData;
  for (double value : data) {
    newData.append(value);
  }

  switch (type) {
  case SensorDataType::RAW:
    // qDebug() << "TrendAPI Setting RAW with data of size " << newData.size();

    // Iterate and print all RAW data values
    // qDebug() << "Printing RAW data values:";
    // for (double value : data) {
    //     qDebug() << value;
    // }
    setRaw(newData);
    break;
  case SensorDataType::SMA:
    // qDebug() << "TrendAPI Setting SMA with size " << newData.size();
    setSma(newData);
    break;
  case SensorDataType::EMA:
    // qDebug() << "TrendAPI Setting EMA with size " << newData.size();
    setEma(newData);
    break;
  default:
    qWarning() << "Unknown sensor data type received!";
    break;
  }
}
