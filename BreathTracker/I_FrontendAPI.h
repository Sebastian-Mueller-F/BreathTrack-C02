#ifndef I_FRONTENDAPI_H
#define I_FRONTENDAPI_H

#include <QObject>
#include <QSettings>



class I_FrontendAPI : public QObject {
 Q_OBJECT

public :

 virtual QVariant getBackendData();
 virtual void handleFrontendRequest();

 virtual void saveSettings(QString key, QVariant val);
 virtual void loadSettings();

 private:

 QSettings _settings;
};


#endif // I_FRONTENDAPI_H

