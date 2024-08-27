#ifndef FRONTENDMODULEMANAGER_H
#define FRONTENDMODULEMANAGER_H

#include <QObject>
#include <QScopedPointer>
#include "databuffermanager.h"
#include "livedataapi.h"
#include "trenddataapi.h"

class FrontendModuleManager : public QObject
{
    Q_OBJECT

public:
    explicit FrontendModuleManager(QObject *parent = nullptr);

    LiveDataAPI *liveDataAPI() const;
    TrendDataAPI *trendDataAPI() const;

private:
    QScopedPointer<LiveDataAPI> _liveDataAPI;
    QScopedPointer<TrendDataAPI> _trendDataAPI;

    std::shared_ptr<DataBufferManager> _dataBufferManager;
};

#endif // FRONTENDMODULEMANAGER_H
