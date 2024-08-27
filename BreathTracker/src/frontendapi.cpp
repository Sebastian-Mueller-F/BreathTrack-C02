#include <frontendapi.h>

FrontendModuleManager::FrontendModuleManager(const BackendDependencies &backendDependencies,
                                             QObject *parent)
    : QObject(parent)
    , _backendDependencies(backendDependencies)
{
    // Initialize _liveDataAPI and _trendDataAPI in the constructor body
    _liveDataAPI.reset(new LiveDataAPI(backendDependencies.sensor.get(),
                                       backendDependencies.smaA.get(),
                                       backendDependencies.emaA.get(),
                                       this));

    _trendDataAPI.reset(new TrendDataAPI(backendDependencies.dataBuffer.get(), this));

    // Initialize TrendDataAPI
    _liveDataAPI->initialize();
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
