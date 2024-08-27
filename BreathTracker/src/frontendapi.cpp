#include "frontendmodulemanager.h"

FrontendModuleManager::FrontendModuleManager(QObject *parent)
    : QObject(parent)
    , _dataBufferManager(DataBufferManager::instance())
    , _liveDataAPI(new LiveDataAPI(SMAAverager::instance().data(),
                                   EMAAverager::instance().data(),
                                   SensorSimulator::instance().get(),
                                   this))
    , _trendDataAPI(new TrendDataAPI(_dataBufferManager.get(), this))
{
    // The TrendDataAPI will handle its own subscriptions using the DataBufferManager
}

LiveDataAPI *FrontendModuleManager::liveDataAPI() const
{
    return _liveDataAPI.data();
}

TrendDataAPI *FrontendModuleManager::trendDataAPI() const
{
    return _trendDataAPI.data();
}
