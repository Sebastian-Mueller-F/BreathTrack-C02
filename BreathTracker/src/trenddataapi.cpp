#include "trenddataapi.h"

QScopedPointer<TrendDataAPI> TrendDataAPI::_instance;

TrendDataAPI::TrendDataAPI(DataBufferManager *dataBufferManager, QObject *parent)
    : QObject(parent)
    , _dataBufferManager(dataBufferManager)
{}

TrendDataAPI::~TrendDataAPI()
{
    qDebug() << "TrendDataAPI destroyed";
}

TrendDataAPI *TrendDataAPI::instance(DataBufferManager *dataBufferManager, QObject *parent)
{
    if (!_instance) {
        _instance.reset(new TrendDataAPI(dataBufferManager, parent));
    }
    return _instance.data();
}

QObject *TrendDataAPI::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return TrendDataAPI::instance();
}

void TrendDataAPI::initialize()
{
    // Subscribe to all relevant buffers and get data from the buffers

    _dataBufferManager->subscribeToAll(std::shared_ptr<I_Subscriber>(this), 50000);
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
