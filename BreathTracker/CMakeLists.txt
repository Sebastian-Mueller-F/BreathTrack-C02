cmake_minimum_required(VERSION 3.16)

set(QT_ENABLE_VERBOSE_DEPLOYMENT TRUE)

project(BreathTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appBreathTracker
    main.cpp
)

qt_add_qml_module(appBreathTracker
    URI BreathTracker
    VERSION 1.0
    QML_FILES main.qml
    SOURCES sensorsimulator.h sensorsimulator.cpp
    SOURCES circularbuffer.h circularbuffer.cpp
    SOURCES buffersubscription.h buffersubscription.cpp
    SOURCES databuffermanager.h databuffermanager.cpp
    SOURCES averager.h
    SOURCES smaaverager.h smaaverager.cpp
    SOURCES subscriber.h
    SOURCES emaaverager.h emaaverager.cpp
    SOURCES types.h
)

source_group("Source Files// Sensor" FILES sensorsimulator.h sensorsimulator.cpp)
source_group("Source Files// Data Structures" FILES circularbuffer.h circularbuffer.cpp buffersubscription.h buffersubscription.cpp subscriber.h)
source_group("Source Files// Data" FILES databuffermanager.h databuffermanager.cpp)
source_group("Source Files// Averager" FILES averager.h smaaverager.h smaaverager.cpp emaaverager.h emaaverager.cpp)
source_group("Source FIles// Utils" Files types.h)



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
