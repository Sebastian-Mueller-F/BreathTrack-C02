#include "emaaverager.h"
#include <stdexcept>
#include <numeric>

EMAAverager::EMAAverager(size_t period, QObject *parent)
    : Averager(parent),  _period(period), _previousEMA(0.0), _isFirstCalculation(true)
{
    //Initialize averageType
    _averageType = AverageTypes::EMA;
    // Calculate alpha
    _alpha = 2.0 / (static_cast<double>(_period) + 1.0);
}

EMAAverager *EMAAverager::instance()
{
    if(_instance == nullptr){
        _instance = new EMAAverager(2);
    }

    return _instance;
}

void EMAAverager::onNewData(const std::vector<double>& data)
{
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
}

double EMAAverager::calculate()
{
    return _previousEMA; // Return the most recently calculated EMA
}

size_t EMAAverager::getPeriod() const {
    return _period;
}

void EMAAverager::setPeriod(size_t period) {
    _period = period;

    // Recalculate alpha based on the new period
    _alpha = 2.0 / (static_cast<double>(_period) + 1.0);

    // Reset the EMA calculation
    _isFirstCalculation = true;
    _previousEMA = 0.0;
}
