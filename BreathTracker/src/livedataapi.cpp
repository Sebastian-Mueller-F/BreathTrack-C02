#include "livedataapi.h"

LiveDataAPI::LiveDataAPI(I_Sensor *sensor,
                         I_Averager *smaAverager,
                         I_Averager *emaAverager,
                         QObject *parent)
    : QObject(parent)
    , _sensor(sensor)
    , _smaAverager(smaAverager)
    , _emaAverager(emaAverager)
    , _sensorValue(0)
    , _averagedValue(0)
    , _averageType(FrontendTypes::AverageType::SMA)
{}

LiveDataAPI::~LiveDataAPI()
{
    /* Alle Signalverbindungen trennen, um sicherzustellen, dass keine
    Verbindungen auf eine gelöschte Instanz zeigen.
    Der Rest wird vom ScopedPointer übernommen. Da die FrontendAPIs eng mit QT verbunden sind
    wurde auch QScopedPointer statt std::unique_ptr verwendet
    */
    disconnect(SensorSimulator::instance().get(), nullptr, this, nullptr);
    disconnect(SMAAverager::instance().get(), nullptr, this, nullptr);
    disconnect(EMAAverager::instance().get(), nullptr, this, nullptr);
}

void LiveDataAPI::initialize()
{
    this->getBackendData();
}

int LiveDataAPI::emaPeriod() const
{
    return _emaPeriod;
}

void LiveDataAPI::setEmaPeriod(int newEmaPeriod)
{
    if (_emaPeriod == newEmaPeriod)
        return;

    _emaPeriod = newEmaPeriod;

    EMAAverager::instance()->setPeriod(_emaPeriod);
    qDebug() << "LiveDataAPI: EMA Period changed to" << _emaPeriod;
    emit emaPeriodChanged();
}

int LiveDataAPI::smaPeriod() const
{
    return _smaPeriod;
}

void LiveDataAPI::setSmaPeriod(int newSmaPeriod)
{
    if (_smaPeriod == newSmaPeriod)
        return;

    _smaPeriod = newSmaPeriod;
    SMAAverager::instance()->setPeriod(_smaPeriod);
    qDebug() << "LiveDataAPI: SMA Period changed to" << _emaPeriod;
    emit smaPeriodChanged();
}

FrontendTypes::AverageType LiveDataAPI::averageType() const
{
    return _averageType;
}

void LiveDataAPI::setAverageType(const FrontendTypes::AverageType &newAverageType)
{
    if (_averageType == newAverageType) {
        return;
    }
    _averageType = newAverageType;
    emit averageTypeChanged();
}

void LiveDataAPI::getBackendData()
{
    // get sensor data
    connect(_sensor, &SensorSimulator::newCo2Value, this, [this](double newValue) {
        int val = static_cast<int>(newValue);
        // qDebug() << "Setting Sensor Value for FE = " << val;
        setSensorValue(val);
    });

    // get averager data
    if (_averageType == 0) {
        connect(_smaAverager, &SMAAverager::averageUpdated, this, [this](double newValue) {
            int val = static_cast<int>(newValue);
            // qDebug() << "Setting SMA Value for FE = " << val;
            setAveragedValue(val);
        });
    } else {
        connect(_emaAverager, &EMAAverager::averageUpdated, this, [this](double newValue) {
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
void LiveDataAPI::updatePeriodInAveragers()
{
    if (_averageType == FrontendTypes::AverageType::SMA) {
        _smaAverager->setPeriod(_smaPeriod);
    } else {
        _emaAverager->setPeriod(_emaPeriod);
    }
}

int LiveDataAPI::sensorValue() const
{
    return _sensorValue;
}

void LiveDataAPI::setSensorValue(int newSensorValue)
{
    if (newSensorValue != _sensorValue) {
        _sensorValue = newSensorValue;
        emit sensorValueChanged();
    }
}

int LiveDataAPI::averagedValue() const
{
    return _averagedValue;
}

void LiveDataAPI::setAveragedValue(int newAveragedValue)
{
    if (newAveragedValue != _averagedValue) {
        _averagedValue = newAveragedValue;
        // qDebug() << "Averaged Value " << newAveragedValue;
        emit averagedValueChanged();
    }
}
