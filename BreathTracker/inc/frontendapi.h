#ifndef FRONTENDMODULEMANAGER_H
#define FRONTENDMODULEMANAGER_H

#include <QObject>
#include <QScopedPointer>
#include "databuffermanager.h"
#include "livedataapi.h"
#include "trenddataapi.h"

struct BackendDependencies
{
    void init(std::shared_ptr<I_Sensor> sensor,
              std::shared_ptr<I_Averager> sma,
              std::shared_ptr<I_Averager> ema,
              std::shared_ptr<DataBufferManager> dataBuffer)
    {
        this->sensor = sensor;
        this->sma = sma;
        this->ema = ema;
        this->dataBuffer = dataBuffer;
    }

    std::shared_ptr<I_Sensor> sensor;
    std::shared_ptr<I_Averager> sma;
    std::shared_ptr<I_Averager> ema;
    std::shared_ptr<DataBufferManager> dataBuffer;
};

class FrontendApi : public QObject
{
    Q_OBJECT

public:
    explicit FrontendApi(const BackendDependencies &backendDependencies, QObject *parent = nullptr);

    LiveDataAPI *liveDataAPI() const;
    TrendDataAPI *trendDataAPI() const;

private:

    BackendDependencies _backendDependencies;
};

#endif // FRONTENDMODULEMANAGER_H
