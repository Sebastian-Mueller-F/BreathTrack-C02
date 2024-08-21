#include "smaaverager.h"
#include <numeric>  // for std::accumulate
#include <stdexcept>

SMAAverager::SMAAverager(size_t period, QObject *parent)
    : Averager(parent), _period(period)
{
    //Initialize averageType
    _averageType = SensorDataType::SMA;
}

SMAAverager *SMAAverager::instance()
{
    if (_instance == nullptr){
        _instance = new SMAAverager(2);
    }

    return _instance;
}

void SMAAverager::onNewData(const std::vector<double>& data)
{
    _recentData = data;
    double sma = calculate();
    emit averageUpdated(sma, this->_averageType);
}

double SMAAverager::calculate()
{
    if (_recentData.empty()) {
        throw std::runtime_error("No data available. Cannot calculate SMA.");
    }

    // Calculate the sum of the recent data
    double sum = std::accumulate(_recentData.begin(), _recentData.end(), 0.0);

    // Calculate the average
    double sma = sum / static_cast<double>(_recentData.size());

    return sma;
}

size_t SMAAverager::getPeriod() const {
    return _period;
}

void SMAAverager::setPeriod(size_t period) {
    _period = period;
}
