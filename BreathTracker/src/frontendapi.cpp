#include <QDebug>
#include <frontendapi.h>

FrontendModuleManager::FrontendModuleManager(const BackendDependencies &backendDependencies,
                                             QObject *parent)
    : QObject(parent)
    , _backendDependencies(backendDependencies)
{
    qDebug() << "frontend api created";

    // Initialize the singletons
    LiveDataAPI::instance(backendDependencies.sensor.get(),
                          backendDependencies.sma.get(),
                          backendDependencies.ema.get(),
                          this)
        ->initialize();

    TrendDataAPI::instance(backendDependencies.dataBuffer.get(), this)->initialize();
}
LiveDataAPI *FrontendModuleManager::liveDataAPI() const
{
    return LiveDataAPI::instance();
}

TrendDataAPI *FrontendModuleManager::trendDataAPI() const
{
    return TrendDataAPI::instance();
}
