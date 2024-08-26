#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sensorsimulator.h>

#include <QLocale>
#include <QTranslator>
#include <QQmlEngine>
#include <QVector>
#include <QMetaType>

#include <circularbuffer.h>
#include <buffersubscription.h>
#include <smaaverager.h>
#include <emaaverager.h>
#include <I_Subscriber.h>
#include <databuffermanager.h>
#include <livedataapi.h>

// Register QVector<double> as a Qt meta-type
Q_DECLARE_METATYPE(QList<double>)

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //register Metatypes
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

    SensorSimulator* CO2sensor = SensorSimulator::instance();
    QSharedPointer<I_Subscriber> sma = SMAAverager::instance();
    QSharedPointer<I_Subscriber> ema = EMAAverager::instance();

    //create buffer for averagers
    CircularBuffer averagerBuffer(60); //TODO: variable instead of hardcoded 6
    //add data from Sensor into averagerBuffer
    QObject::connect(SensorSimulator::instance(), &SensorSimulator::newCo2Value, [&] (double newCo2Value){
        averagerBuffer.writeNewItem(newCo2Value);
    });
    BufferSubscription averagerBufferSubscription(averagerBuffer);
    averagerBufferSubscription.registerSubscriber(sma, 5000, SensorDataType::RAW); //5 seconds
    averagerBufferSubscription.registerSubscriber(ema, 10000, SensorDataType::RAW); // 10 seconds

    std::shared_ptr<DataBufferManager> dataBuffer = DataBufferManager::instance();

    QQmlApplicationEngine engine;

    qmlRegisterType<FrontendTypes>("BreathTracker.FrontendTypes", 1, 0, "FrontendTypes");
    qmlRegisterSingletonType<LiveDataAPI>("BreathTracker.LiveData", 1, 0, "BELiveData", LiveDataAPI::qmlInstance);
    qmlRegisterSingletonType<TrendDataAPI>("BreathTracker.TrendData", 1, 0, "BETrendData", TrendDataAPI::qmlInstance);
    LiveDataAPI::instance();
    TrendDataAPI::instance();


    const QUrl url(QStringLiteral("qrc:/BreathTracker/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    //Frontend API


    return app.exec();
}
