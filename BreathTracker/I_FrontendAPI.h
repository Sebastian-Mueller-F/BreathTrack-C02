#ifndef I_FRONTENDAPI_H
#define I_FRONTENDAPI_H

#include <QObject>
#include <QSettings>



class I_FrontendAPI : public QObject {
 Q_OBJECT

public :

 virtual QVariant getBackendData() = 0;
 virtual void handleFrontendRequest() = 0;

 virtual void saveSettings(QString key, QVariant val) = 0;
 virtual void loadSettings() = 0;

};


#endif // I_FRONTENDAPI_H

