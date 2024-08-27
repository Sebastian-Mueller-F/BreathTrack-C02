#ifndef EMAAVERAGER_H
#define EMAAVERAGER_H

#include <QObject>
#include <QSharedPointer>

#include "I_Averager.h"
#include "I_Subscriber.h"
#include <types.h>

class EMAAverager : public I_Averager, public I_Subscriber {
  Q_OBJECT

public:
  EMAAverager(size_t period, QObject *parent = nullptr);

  ~EMAAverager() override;
  ;

  // singleton
  static std::shared_ptr<EMAAverager> instance();

  double calculate() override;
  size_t getPeriod() const override;
  void setPeriod(size_t period) override;

  // Implement the Subscriber interface
  void onNewData(const std::vector<double> &data,
                 SensorDataType type = SensorDataType::RAW) override;
  void onPeriodChanged() override;

private:
  // singleton
    static std::shared_ptr<EMAAverager> _instance;

    size_t _period;
    double _previousEMA;
    bool _isFirstCalculation;
    double _alpha;
};

#endif // EMAAVERAGER_H
