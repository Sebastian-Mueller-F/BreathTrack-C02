#include <QGuiApplication>
#include <QLocale>
#include <QMetaType>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QTranslator>
#include <QVector>

#include <averagecalculator.h>
#include <buffersubscription.h>
#include <databuffermanager.h>
#include <emaaverager.h>
#include <frontendapi.h>
#include <i_sensor.h>
#include <iostream>
#include <livedataapi.h>
#include <sensorfactory.h>
#include <sensorsimulator.h>
#include <smaaverager.h>

void printCppVersion()
{
    std::cout << "__cplusplus value: " << __cplusplus << std::endl;

    if (__cplusplus == 201703L) {
        std::cout << "C++17 is used." << std::endl;
    } else if (__cplusplus == 201402L) {
        std::cout << "C++14 is used." << std::endl;
    } else if (__cplusplus == 201103L) {
        std::cout << "C++11 is used." << std::endl;
    } else if (__cplusplus == 199711L) {
        std::cout << "C++98 is used." << std::endl;
    } else if (__cplusplus == 202002L) {
        std::cout << "C++20 is used." << std::endl;
    } else {
        std::cout << "A newer or unknown C++ version is used." << std::endl;
    }
}

struct PermanentBackendObjects
{
    PermanentBackendObjects(std::shared_ptr<BackendDependencies> backendDeps,
                            std::shared_ptr<AverageCalculator> avgCalc)
        : backendDependencies(backendDeps)
        , avgCalc(avgCalc)
    {}

    std::shared_ptr<BackendDependencies> backendDependencies;
    std::shared_ptr<AverageCalculator> avgCalc;
};

void initializeTranslator(QGuiApplication &app)
{
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "BreathTracker_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
}

// initalize backend und return pointer to all backend objects that need to be kept alive
std::unique_ptr<PermanentBackendObjects> initializeBackend()
{
    // Initialize the sensor (using the simulator for now)
    std::shared_ptr<I_Sensor> sensor = SensorFactory::createSensor(
        true); // Change to false when using the hardware sensor
    if (sensor == nullptr) {
        qCritical() << "Failed to initialize CO2 sensor.";
        return nullptr;
    }
    sensor->startMeasurement();

    // Initialize AverageCalculator
    auto avgCalc = std::make_shared<AverageCalculator>(sensor, 60); // Buffer size 60
    avgCalc->start();

    //get address from SMA und EMA singletons which already were created within the AverageCaalculator object
    auto sma = SMAAverager::instance();
    auto ema = EMAAverager::instance();

    // Initialize DataBufferManager
    auto trendDataBuffer = DataBufferManager::instance(sensor, sma, ema);

    // Create and initialize BackendDependencies
    auto backendDependenciesForFrontend = std::make_shared<BackendDependencies>();
    backendDependenciesForFrontend->init(sensor, sma, ema, trendDataBuffer);

    // Return the permanent backend objects wrapped in a unique_ptr
    return std::make_unique<PermanentBackendObjects>(backendDependenciesForFrontend, avgCalc);
}

// Function to initialize QML engine
void initializeQmlEngine(QQmlApplicationEngine &engine,
                         QGuiApplication &app,
                         FrontendApi &frontendApi)
{
    qmlRegisterType<FrontendTypes>("BreathTracker.FrontendTypes", 1, 0, "FrontendTypes");
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
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Initialize translator
    initializeTranslator(app);

    // Initialize backend
    auto permanentBackendObjects = initializeBackend();
    if (!permanentBackendObjects) {
        throw std::runtime_error("Failed to initialize backend.");
    }

    // Initialize frontend API with backend dependencies
    FrontendApi frontendApi(*permanentBackendObjects->backendDependencies);

    // Initialize QML engine
    QQmlApplicationEngine engine;
    initializeQmlEngine(engine, app, frontendApi);

    printCppVersion();

    // Execute application
    return app.exec();
}
