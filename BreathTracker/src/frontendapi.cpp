#include <frontendapi.h>

FrontendModuleManager::FrontendModuleManager(QObject *parent)
    : QObject(parent)
    , _dataBufferManager(DataBufferManager::instance())
    , _liveDataAPI(new LiveDataAPI(SMAAverager::instance().get(),
                                   EMAAverager::instance().get(),
                                   SensorSimulator::instance().get(),
                                   this))
    , _trendDataAPI(new TrendDataAPI(_dataBufferManager.get(), this))
{
    // Initialize TrendDataAPI
    _trendDataAPI->initialize();
}

LiveDataAPI *FrontendModuleManager::liveDataAPI() const
{
    return _liveDataAPI.data();
}

TrendDataAPI *FrontendModuleManager::trendDataAPI() const
{
    return _trendDataAPI.data();
}
