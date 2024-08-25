#ifndef FRONTENDTYPES_H
#define FRONTENDTYPES_H

#include <QObject>

class FrontendTypes : public QObject {
    Q_OBJECT
public:
    enum AverageType {
        SMA,
        EMA
    };
    Q_ENUM(AverageType)
};

#endif // FRONTENDTYPES_H
