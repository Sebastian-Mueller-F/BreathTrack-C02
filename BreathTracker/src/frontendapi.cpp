#include <QDebug>
#include <frontendapi.h>

FrontendApi::FrontendApi(const BackendDependencies &backendDependencies, QObject *parent)
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
LiveDataAPI *FrontendApi::liveDataAPI() const
{
    return LiveDataAPI::instance();
}

TrendDataAPI *FrontendApi::trendDataAPI() const
{
    return TrendDataAPI::instance();
}
