#ifndef I_FRONTENDAPIMODULE_H
#define I_FRONTENDAPIMODULE_H

#include <QObject>
#include <QSettings>

class I_FrontendAPIModule
{
public:
  virtual void getBackendData() = 0;
  virtual void handleFrontendRequest() = 0;

  virtual void saveSettings(QString key, QVariant val) = 0;
  virtual void loadSettings() = 0;

  virtual ~I_FrontendAPIModule() = default;
};

#endif // I_FRONTENDAPIMODULE_H
