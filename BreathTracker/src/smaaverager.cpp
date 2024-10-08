#include "smaaverager.h"
#include <QDebug>
#include <numeric> // for std::accumulate
#include <stdexcept>

std::shared_ptr<SMAAverager> SMAAverager::_instance = nullptr;

SMAAverager::SMAAverager(size_t period, QObject *parent)
    : I_Averager(parent), _period(period) {
  // Initialize averageType
  _averageType = SensorDataType::SMA;
}

SMAAverager::~SMAAverager()
{
    qDebug() << "SMA Averager destroyed";

    bool disconnected = disconnect(this, nullptr, nullptr, nullptr);
    if (disconnected) {
        qDebug() << "Successfully disconnected all signals for SMAAverager.";
    } else {
        qWarning() << "No signals to disconnect or disconnection failed!";
    }

    _instance.reset();
}

std::shared_ptr<SMAAverager> SMAAverager::instance(size_t period, QObject *parent)
{
    if (_instance == nullptr) {
        _instance = std::shared_ptr<SMAAverager>(new SMAAverager(period, parent));
        qDebug() << "SMAAverager Singleton instance created.";
    }
    return _instance;
}

void SMAAverager::onNewData(const std::vector<double> &data,
                            SensorDataType type) {
    qDebug() << "SMA On New Data";
    _recentData = data;

    double sma = calculate();

    emit averageUpdated(sma, this->_averageType);
    qDebug() << "Emitted averageUpdated signal with SMA:" << sma;
}

double SMAAverager::calculate() {
  if (_recentData.empty()) {
    throw std::runtime_error("No data available. Cannot calculate SMA.");
  }

  // Adjust calculation if the period is greater than the amount of available
  // data
  size_t numDataPoints = std::min(_period, _recentData.size());

  // Calculate the sum of the recent data
  double sum = std::accumulate(_recentData.end() - numDataPoints,
                               _recentData.end(), 0.0);

  // Calculate the average
  double sma = sum / static_cast<double>(numDataPoints);

  return sma;
}

size_t SMAAverager::getPeriod() const { return _period; }

void SMAAverager::setPeriod(size_t period) {
  _period = period;
  onPeriodChanged(); // Recalculate or adjust internal state
}

void SMAAverager::onPeriodChanged() {
  // Adjust the size of _recentData based on the new period
  if (_recentData.size() > _period) {
    // If the period is reduced, discard the oldest data
    _recentData.erase(_recentData.begin(), _recentData.end() - _period);
  }

  qDebug() << "SMAAverager: Period changed to" << _period;
  // If the period is increased, the existing data remains valid, and future
  // data will fill in
}
