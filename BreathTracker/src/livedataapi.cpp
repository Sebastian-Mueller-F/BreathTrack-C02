#include "livedataapi.h"

QScopedPointer<LiveDataAPI> LiveDataAPI::_instance;

LiveDataAPI::LiveDataAPI(QObject *parent)
    : QObject(parent), _sensorValue(0), _averagedValue(0),
      _averageType(FrontendTypes::AverageType::SMA) {
  this->getBackendData();
}

LiveDataAPI::~LiveDataAPI()
{
    /* Alle Signalverbindungen trennen, um sicherzustellen, dass keine
    Verbindungen auf eine gelöschte Instanz zeigen.
    Der Rest wird vom ScopedPointer übernommen. Da die FrontendAPIs eng mit QT verbunden sind
    wurde auch QScopedPointer statt std::unique_ptr verwendet
    */
    disconnect(SensorSimulator::instance().get(), nullptr, this, nullptr);
    disconnect(SMAAverager::instance().data(), nullptr, this, nullptr);
    disconnect(EMAAverager::instance().data(), nullptr, this, nullptr);
}

// QML INSTANCE
QObject *LiveDataAPI::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {
  Q_UNUSED(scriptEngine)
  Q_UNUSED(engine)

  return LiveDataAPI::instance();
}

LiveDataAPI *LiveDataAPI::instance() {
    if (!_instance) {
        _instance.reset(new LiveDataAPI);
    }
    return _instance.data();
}

int LiveDataAPI::emaPeriod() const { return _emaPeriod; }

void LiveDataAPI::setEmaPeriod(int newEmaPeriod) {
  if (_emaPeriod == newEmaPeriod)
    return;

  _emaPeriod = newEmaPeriod;

  EMAAverager::instance()->setPeriod(_emaPeriod);
  qDebug() << "LiveDataAPI: EMA Period changed to" << _emaPeriod;
  emit emaPeriodChanged();
}

int LiveDataAPI::smaPeriod() const { return _smaPeriod; }

void LiveDataAPI::setSmaPeriod(int newSmaPeriod) {
  if (_smaPeriod == newSmaPeriod)
    return;

  _smaPeriod = newSmaPeriod;
  SMAAverager::instance()->setPeriod(_smaPeriod);
  qDebug() << "LiveDataAPI: SMA Period changed to" << _emaPeriod;
  emit smaPeriodChanged();
}

FrontendTypes::AverageType LiveDataAPI::averageType() const {
  return _averageType;
}

void LiveDataAPI::setAverageType(
    const FrontendTypes::AverageType &newAverageType) {
  if (_averageType == newAverageType) {
    return;
  }
  _averageType = newAverageType;
  emit averageTypeChanged();
}

void LiveDataAPI::getBackendData() {
  // get sensor data
  connect(SensorSimulator::instance().get(),
          &SensorSimulator::newCo2Value,
          this,
          [this](double newValue) {
              int val = static_cast<int>(newValue);
              // qDebug() << "Setting Sensor Value for FE = " << val;
              setSensorValue(val);
          });

  // get averager data
  if (_averageType == 0) {
    connect(SMAAverager::instance().data(), &SMAAverager::averageUpdated, this,
            [this](double newValue) {
              int val = static_cast<int>(newValue);
              // qDebug() << "Setting SMA Value for FE = " << val;
              setAveragedValue(val);
            });
  } else {
    connect(EMAAverager::instance().data(), &EMAAverager::averageUpdated, this,
            [this](double newValue) {
              int val = static_cast<int>(newValue);
              // qDebug() << "Setting EMA Value for FE = " << val;
              setAveragedValue(val);
            });
  }
}

void LiveDataAPI::handleFrontendRequest() {}

void LiveDataAPI::saveSettings(QString key, QVariant val) {}

void LiveDataAPI::loadSettings() {}

// TODO: either delete or update
void LiveDataAPI::updatePeriodInAveragers() {
  if (_averageType == FrontendTypes::AverageType::SMA) {
    SMAAverager::instance()->setPeriod(_smaPeriod);
  } else {
    EMAAverager::instance()->setPeriod(_emaPeriod);
  }
}

int LiveDataAPI::sensorValue() const { return _sensorValue; }

void LiveDataAPI::setSensorValue(int newSensorValue) {
  if (newSensorValue != _sensorValue) {
    _sensorValue = newSensorValue;
    emit sensorValueChanged();
  }
}

int LiveDataAPI::averagedValue() const { return _averagedValue; }

void LiveDataAPI::setAveragedValue(int newAveragedValue) {
  if (newAveragedValue != _averagedValue) {
    _averagedValue = newAveragedValue;
    // qDebug() << "Averaged Value " << newAveragedValue;
    emit averagedValueChanged();
  }
}
