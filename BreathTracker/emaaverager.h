#ifndef EMAAVERAGER_H
#define EMAAVERAGER_H

#include <QObject>
#include <QSharedPointer>

#include "averager.h"
#include "subscriber.h"


class EMAAverager : public Averager, public Subscriber {
    Q_OBJECT

public:
    EMAAverager(size_t period, QObject *parent = nullptr);

    ~EMAAverager() override {
        // Destructor code, if any specific cleanup is needed
    }

    //singleton
    static QSharedPointer<EMAAverager> instance();

    double calculate() override;
    size_t getPeriod() const override;
    void setPeriod(size_t period) override;

    // Implement the Subscriber interface
    void onNewData(const std::vector<double>& data) override ;

private:
    //singleton
    static QSharedPointer<EMAAverager> _instance;

    size_t _period;
    double _previousEMA;
    bool _isFirstCalculation;
    double _alpha;
};

#endif // EMAAVERAGER_H
