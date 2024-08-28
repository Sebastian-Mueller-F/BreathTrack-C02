#include "sensorsimulator.h"
#include <QDebug>
#include <QRandomGenerator>

std::shared_ptr<SensorSimulator> SensorSimulator::_instance = nullptr;

SensorSimulator::SensorSimulator(double baseline, double amplitude, int interval, QObject *parent)
    : I_Sensor(parent)
    , // Initialize QObject
    _baseline(baseline)
    , _amplitude(amplitude)
    , _interval(interval)
    , _sensorDataType(SensorDataType::RAW)
{
    _timer.reset(new QTimer(this));

    // Connect timer to the generateNewCo2Value slot
    connect(_timer.data(), &QTimer::timeout, this, &SensorSimulator::generateNewCo2Value);

    // Example debug output connection
    connect(this,
            &SensorSimulator::newCo2ValueGenerated,
            [&](double sensorValue, SensorDataType type) {
                // qDebug() << "Sensor Co2 value: " << sensorValue;
            });
}

SensorSimulator::~SensorSimulator()
{
    if (_timer && _timer->isActive()) {
        _timer->stop();
        qDebug() << "SensorSim timer stopped in destructor.";
    }

    // Explicitly disconnect any connections
    disconnect(_timer.data(), &QTimer::timeout, this, &SensorSimulator::generateNewCo2Value);
    disconnect(this, &SensorSimulator::newCo2ValueGenerated, nullptr, nullptr);

    // Log the destruction for debugging
    qDebug() << "SensorSimulator destroyed.";

    // Da QScopedPointer automatisch aufgeräumt wird, ist hier keine zusätzliche Implementierung nötig
    // Falls zusätzliche dynamische Ressourcen hinzugefügt werden, sollten sie hier freigegeben werden
}

std::shared_ptr<SensorSimulator> SensorSimulator::instance()
{
    if (!_instance) {
        _instance = std::shared_ptr<SensorSimulator>(new SensorSimulator());
        qDebug() << "SensorSimulator Singleton instance created.";
    }
    return _instance;
}

void SensorSimulator::startMeasurement() {
  if (!_timer->isActive()) {
    _timer->start(_interval);
    qDebug() << "Sensor Sim measurement started.";
  }
}

void SensorSimulator::stopMeasurement() {
  if (_timer->isActive()) {
    _timer->stop();
    qDebug() << "Sensor Sim measurement stopped.";
  }
}

SensorDataType SensorSimulator::sensorDataType() const {
  return _sensorDataType;
}

void SensorSimulator::generateNewCo2Value() {
  double random =
      QRandomGenerator::global()->generateDouble(); // Value between 0 and 1
  double transformedValue = 2.0 * random - 1.0;     // Value between -1 and 1

  double sensorValue = _baseline + (transformedValue * _amplitude);

  emit newCo2ValueGenerated(sensorValue, _sensorDataType);
}
