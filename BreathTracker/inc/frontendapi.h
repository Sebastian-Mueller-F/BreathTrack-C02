#ifndef FRONTENDMODULEMANAGER_H
#define FRONTENDMODULEMANAGER_H

#include <QObject>
#include <QScopedPointer>
#include "databuffermanager.h"
#include "livedataapi.h"
#include "trenddataapi.h"

struct BackendDependencies
{
    std::shared_ptr<I_Sensor> sensor;
    std::shared_ptr<I_Averager> sma;
    std::shared_ptr<I_Averager> ema;
    std::shared_ptr<DataBufferManager> dataBuffer;

    // Constructor (optional) to initialize the struct
    BackendDependencies(std::shared_ptr<I_Sensor> sensor,
                        std::shared_ptr<I_Averager> sma,
                        std::shared_ptr<I_Averager> ema,
                        std::shared_ptr<DataBufferManager> buffer)
        : sensor(sensor)
        , sma(sma)
        , ema(ema)
        , dataBuffer(buffer)
    {}
};

class FrontendModuleManager : public QObject
{
    Q_OBJECT

public:
    explicit FrontendModuleManager(const BackendDependencies &backendDependencies,
                                   QObject *parent = nullptr);

    LiveDataAPI *liveDataAPI() const;
    TrendDataAPI *trendDataAPI() const;

private:
    QScopedPointer<LiveDataAPI> _liveDataAPI;
    QScopedPointer<TrendDataAPI> _trendDataAPI;

    BackendDependencies _backendDependencies;
};

#endif // FRONTENDMODULEMANAGER_H
