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
#include <buffersubscription.h>
#include <circularbuffer.h>
#include <databuffermanager.h>
#include <emaaverager.h>
#include <livedataapi.h>
#include <sensorfactory.h>
#include <smaaverager.h>

// Register QVector<double> as a Qt meta-type
Q_DECLARE_METATYPE(QList<double>)

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  // register Metatypes
  int registeredQList = qRegisterMetaType<QList<double>>("QList<double>");

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
  I_Sensor *CO2sensor = SensorFactory::createSensor(
      true); // Change to false when using the hardware sensor
  if (CO2sensor == nullptr) {
    qCritical() << "Failed to initialize CO2 sensor.";
    return -1;
  }
  CO2sensor->startMeasurement();

  QSharedPointer<I_Subscriber> sma = SMAAverager::instance();
  QSharedPointer<I_Subscriber> ema = EMAAverager::instance();

  // create buffer for averagers
  CircularBuffer averagerBuffer(60); // TODO: variable instead of hardcoded 6
  // add data from Sensor into averagerBuffer
  bool receivingSensorDataSucess = QObject::connect(
      CO2sensor, &I_Sensor::newCo2Value,
      [&](double newCo2Value) { averagerBuffer.writeNewItem(newCo2Value); });
  if (!receivingSensorDataSucess) {
    qCritical() << "Failed to connect signal to slot!";
  }

  BufferSubscription averagerBufferSubscription(averagerBuffer);
  averagerBufferSubscription.registerSubscriber(
      sma, 5000, SensorDataType::RAW); // 5 seconds
  averagerBufferSubscription.registerSubscriber(
      ema, 10000, SensorDataType::RAW); // 10 seconds

  std::shared_ptr<DataBufferManager> dataBuffer = DataBufferManager::instance();

  QQmlApplicationEngine engine;

  qmlRegisterType<FrontendTypes>("BreathTracker.FrontendTypes", 1, 0,
                                 "FrontendTypes");
  qmlRegisterSingletonType<LiveDataAPI>("BreathTracker.LiveData", 1, 0,
                                        "BELiveData", LiveDataAPI::qmlInstance);
  qmlRegisterSingletonType<TrendDataAPI>("BreathTracker.TrendData", 1, 0,
                                         "BETrendData",
                                         TrendDataAPI::qmlInstance);
  LiveDataAPI::instance();
  TrendDataAPI::instance();

  const QUrl url(QStringLiteral("qrc:/BreathTracker/main.qml"));
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
