#include "livedataapi.h"

LiveDataAPI* LiveDataAPI::_instance = nullptr;

LiveDataAPI::LiveDataAPI (QObject *parent) :
    QObject(parent),
    _sensorValue(0),
    _averagedValue(0),
    _averageType(0)
{
    this->getBackendData();
}

//QML INSTANCE
QObject *LiveDataAPI::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)
    Q_UNUSED(engine)

    return LiveDataAPI::instance();

}

 LiveDataAPI* LiveDataAPI::instance()
{
    if (!_instance){
            _instance = new LiveDataAPI;
        }

        return _instance;
}

void LiveDataAPI::getBackendData()
{
    //get sensor data
    connect(SensorSimulator::instance(), &SensorSimulator::newCo2Value, this, [this](double newValue){
        int val = static_cast<int>(newValue);
        qDebug() << "Setting Sensor Value for FE = " << val;
        setSensorValue(val);
    });

    //get averager data
    if(_averageType == 0){
        connect (SMAAverager::instance().data(), &SMAAverager::averageUpdated,  this, [this] (double newValue) {
            int val = static_cast<int>(newValue);
            qDebug() << "Setting SMA Value for FE = " << val;
            setAveragedValue(val);
        });
    } else {
        connect (EMAAverager::instance().data(), &EMAAverager::averageUpdated,  this, [this] (double newValue) {
            int val = static_cast<int>(newValue);
            qDebug() << "Setting EMA Value for FE = " << val;
            setAveragedValue(val);
        });
    }

}

void LiveDataAPI::handleFrontendRequest()
{

}

void LiveDataAPI::saveSettings(QString key, QVariant val)
{

}

void LiveDataAPI::loadSettings()
{

}

int LiveDataAPI::sensorValue() const
{
    return _sensorValue;
}

void LiveDataAPI::setSensorValue(int newSensorValue)
{
    if (newSensorValue != _sensorValue){
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
    if (newAveragedValue != _averagedValue){
        _averagedValue = newAveragedValue;
        qDebug() << "Averaged Value " << newAveragedValue;
        emit averagedValueChanged();
    }
}
