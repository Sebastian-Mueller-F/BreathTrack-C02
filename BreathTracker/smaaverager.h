#ifndef SMAAVERAGER_H
#define SMAAVERAGER_H

#include "subscriber.h"
#include "averager.h"
#include <QObject>

class SMAAverager : public Averager, public Subscriber {
    Q_OBJECT

public:
    SMAAverager(size_t period, QObject *parent = nullptr);

    double calculate() override;
    size_t getPeriod() const override;
    void setPeriod(size_t period) override;

    // Implement the Subscriber interface
    void onNewData(const std::vector<double>& data) override;

private:
    static SMAAverager* _instance;

    size_t _period;
    std::vector<double> _recentData;
};

#endif // SMAAVERGER_H
