#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sensorsimulator.h>

#include <QLocale>
#include <QMetaType>
#include <QQmlEngine>
#include <QTranslator>
#include <QVector>

#include <I_Sensor.h>
#include <I_Subscriber.h>
#include <averagecalculator.h>
#include <buffersubscription.h>
#include <circularbuffer.h>
#include <databuffermanager.h>
#include <emaaverager.h>
#include <frontendapi.h>
#include <livedataapi.h>
#include <sensorfactory.h>
#include <smaaverager.h>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "BreathTracker_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      app.installTranslator(&translator);
      break;
    }
  }

  // Initialize the sensor (using the simulator for now)
  std::shared_ptr<I_Sensor> sensor = SensorFactory::createSensor(
      true); // Change to false when using the hardware sensor
  if (sensor == nullptr) {
      qCritical() << "Failed to initialize CO2 sensor.";
      return -1;
  }
  sensor->startMeasurement();

  AverageCalculator avgCalc(sensor, 60); // Puffergröße 60, könnte auch konfigurierbar sein
  avgCalc.start();

  std::shared_ptr<I_Averager> sma = SMAAverager::instance();
  std::shared_ptr<I_Averager> ema = EMAAverager::instance();

  std::shared_ptr<DataBufferManager> dataBuffer = DataBufferManager::instance(sensor, sma, ema);

  BackendDependencies backendDeps(sensor, sma, ema, dataBuffer);

  FrontendApi frontendApi(backendDeps);

  QQmlApplicationEngine engine;

  qmlRegisterType<FrontendTypes>("BreathTracker.FrontendTypes", 1, 0,
                                 "FrontendTypes");
  qmlRegisterSingletonType<LiveDataAPI>("BreathTracker.LiveData",
                                        1,
                                        0,
                                        "BELiveData",
                                        LiveDataAPI::qmlInstance);
  qmlRegisterSingletonType<TrendDataAPI>("BreathTracker.TrendData",
                                         1,
                                         0,
                                         "BETrendData",
                                         TrendDataAPI::qmlInstance);

  const QUrl url(QStringLiteral("qrc:/BreathTracker/qml/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  // Frontend API

  return app.exec();
}
