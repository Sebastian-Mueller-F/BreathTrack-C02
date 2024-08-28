#ifndef SMAAVERAGER_H
#define SMAAVERAGER_H

#include <QObject>
#include <QSharedPointer>

#include "i_averager.h"
#include "i_subscriber.h"
#include <types.h>

// TODO: 1. do we need period ?
// TODO 2. do we need to limit the number of values that are being taking into
// account for the averager ?

class SMAAverager : public I_Averager, public I_Subscriber
{
    Q_OBJECT

public:
  SMAAverager(size_t period, QObject *parent = nullptr);

  ~SMAAverager() override;

  static std::shared_ptr<SMAAverager> instance(size_t period = 10, QObject *parent = nullptr);

  double calculate() override;
  size_t getPeriod() const override;
  void setPeriod(size_t period) override;

  // Implement the Subscriber interface
  void onNewData(const std::vector<double> &data,
                 SensorDataType type = SensorDataType::RAW) override;
  void onPeriodChanged() override;

private:
    static std::shared_ptr<SMAAverager> _instance;

    size_t _period;
    std::vector<double> _recentData;
};

#endif // SMAAVERGER_H
