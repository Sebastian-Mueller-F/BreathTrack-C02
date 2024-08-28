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

FrontendApi::~FrontendApi()
{
    qDebug() << "Destroying FrontendApi";

    // Should automatically deleted modules as this is the parent
}

LiveDataAPI *FrontendApi::liveDataAPI() const
{
    return LiveDataAPI::instance();
}

TrendDataAPI *FrontendApi::trendDataAPI() const
{
    return TrendDataAPI::instance();
}
