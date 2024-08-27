cmake_minimum_required(VERSION 3.16)

set(QT_ENABLE_VERBOSE_DEPLOYMENT TRUE)

project(BreathTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(${CMAKE_SOURCE_DIR}/inc)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

# Source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp" "inc/*.h")

# Add executable with Qt
qt_add_executable(appBreathTracker
    ${SOURCES}
)

# Qt Add QML Module
qt_add_qml_module(appBreathTracker
    URI BreathTracker
    VERSION 1.0
    # QML Files
    QML_FILES
    qml/main.qml
    qml/DataTrends.qml
    qml/LiveData.qml
    qml/LiveDataBackground.qml
    qml/SettingsDrawer.qml
    qml/SettingsSection.qml
    qml/ArcRight.qml
    qml/ArcLeft.qml
    qml/ArcItem.qml
    qml/CircleIndicator.qml
    qml/CustomLabel.qml
    RESOURCES
    qml/images/ema.png
    qml/images/sma.png
    qml/images/raw.png
    qml/images/assist.png
    qml/images/speed.png
    qml/images/calories.png
)

# Sensor
source_group("Header Files//  Sensor" FILES inc/sensorsimulator.h  inc/I_Sensor.h inc/sensorfactory.h)
source_group("Source Files// Header Files // Sensor" FILES src/sensorsimulator.cpp)

# Data Structures
source_group("Header Files// Data Structures" FILES inc/circularbuffer.h inc/buffersubscription.h inc/I_Subscriber.h)
source_group("Source Files// Data Structures" FILES src/circularbuffer.cpp src/buffersubscription.cpp)

# Data Management
source_group("Header Files// Data" FILES inc/databuffermanager.h)
source_group("Source Files// Data" FILES src/databuffermanager.cpp)

# Averagers
source_group("Header Files// Averager" FILES inc/I_Averager.h inc/smaaverager.h inc/emaaverager.h)
source_group("Source Files// Averager" FILES src/smaaverager.cpp src/emaaverager.cpp)

# Backend Frontend Interface
source_group("Header Files// Backend Frontend Interface" FILES inc/I_FrontendAPI.h inc/I_FrontendAPIModule.h inc/livedataapi.h inc/trenddataapi.h)
source_group("Source Files// Backend Frontend Interface" FILES src/livedataapi.cpp src/trenddataapi.cpp)

# Utils
source_group("Header Files// Utils" FILES inc/types.h inc/FrontendTypes.h)

# QML Files
source_group("QML" FILES qml/main.qml qml/LiveData.qml qml/LiveDataBackground.qml qml/LiveDataMeter.qml qml/DataTrends.qml)
source_group("QML// Components // Arcs" FILES qml/ArcItem.qml qml/ArcLeft.qml qml/ArcRight.qml qml/CircleIndicator.qml)
source_group("QML// Components" FILES qml/CustomLabel.qml qml/ModeToggle.qml qml/SettingsDrawer.qml qml/SettingsSection.qml)




# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appBreathTracker PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appBreathTracker
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appBreathTracker
    PRIVATE Qt6::Quick Qt6::Core Qt6::Gui)


include(GNUInstallDirs)
install(TARGETS appBreathTracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
