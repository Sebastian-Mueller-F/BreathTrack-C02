#include "emaaverager.h"
#include <QDebug>
#include <stdexcept>

std::shared_ptr<EMAAverager> EMAAverager::_instance = nullptr;

EMAAverager::EMAAverager(size_t period, QObject *parent)
    : I_Averager(parent), _period(period), _previousEMA(0.0),
      _isFirstCalculation(true) {
  // Initialize averageType
  _averageType = SensorDataType::EMA;
  // Calculate alpha
  _alpha = 2.0 / (static_cast<double>(_period) + 1.0);
}

EMAAverager::~EMAAverager()
{
    qDebug() << "EMA Averager destroyed";
}

std::shared_ptr<EMAAverager> EMAAverager::instance()
{
    if (_instance == nullptr) {
        _instance = std::shared_ptr<EMAAverager>(new EMAAverager(10));
        qDebug() << "EMAAverager Singleton instance created.";
    }
    return _instance;
}

void EMAAverager::onNewData(const std::vector<double> &data,
                            SensorDataType type) {
  if (data.empty()) {
    throw std::runtime_error("No data available. Cannot calculate EMA.");
  }

  // Calculate the EMA for the most recent data point
  double currentData = data.back();

  if (_isFirstCalculation) {
    // On the first calculation, just set EMA to the current data point
    _previousEMA = currentData;
    _isFirstCalculation = false;
  } else {
    // Apply the EMA formula
    _previousEMA = _alpha * currentData + (1.0 - _alpha) * _previousEMA;
  }
  emit averageUpdated(_previousEMA, this->_averageType);
  // qDebug() << "Emitted averageUpdated signal with EMA:" << _previousEMA;
}

double EMAAverager::calculate() {
  return _previousEMA; // Return the most recently calculated EMA
}

size_t EMAAverager::getPeriod() const { return _period; }

void EMAAverager::setPeriod(size_t period) {
  _period = period;
  onPeriodChanged();
}

void EMAAverager::onPeriodChanged() {
  // Recalculate alpha based on the new period
  _alpha = 2.0 / (static_cast<double>(_period) + 1.0);

  // Reset the EMA calculation
  _isFirstCalculation = true;
  _previousEMA = 0.0;

  qDebug() << "EMAAverager: Period changed to" << _period
           << ", alpha recalculated to" << _alpha;
}
