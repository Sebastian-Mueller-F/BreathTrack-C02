#include "smaaverager.h"
#include <numeric>  // for std::accumulate
#include <stdexcept>
#include <QDebug>

QSharedPointer<SMAAverager> SMAAverager::_instance = nullptr;

SMAAverager::SMAAverager(size_t period, QObject *parent)
    : I_Averager(parent), _period(period)
{
    //Initialize averageType
    _averageType = SensorDataType::SMA;
}


QSharedPointer<SMAAverager> SMAAverager::instance()
{
    if (_instance.isNull()) {
        _instance = QSharedPointer<SMAAverager>::create(2);
    }
    return _instance;
}

//Todo: Handle case for first value
/*Bug:
 *  Sensor Co2 value :  49.1481
Emitted averageUpdated signal with SMA: 0

 Sensor Co2 value :  53.1448
Emitted averageUpdated signal with SMA: 0


 Sensor Co2 value :  57.5672
Emitted averageUpdated signal with SMA: 16.3827

 */
void SMAAverager::onNewData(const std::vector<double>& data, SensorDataType type)
{
    _recentData = data;

    double sma = calculate();

    emit averageUpdated(sma, this->_averageType);
    // qDebug() << "Emitted averageUpdated signal with SMA:" << sma;
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
