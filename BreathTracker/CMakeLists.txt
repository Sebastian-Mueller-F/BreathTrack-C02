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
    SOURCES I_Averager.h
    SOURCES smaaverager.h smaaverager.cpp
    SOURCES I_Subscriber.h
    SOURCES emaaverager.h emaaverager.cpp
    SOURCES types.h
    QML_FILES RawSensorData.qml
    QML_FILES AveragedSensorData.qml
    QML_FILES DataTrends.qml
    SOURCES I_FrontendAPI.h
    SOURCES livedataapi.h livedataapi.cpp
    SOURCES trenddataapi.h trenddataapi.cpp
    QML_FILES ArcItem.qml ArcLeft.qml ArcRight.qml CircleIndicator.qml CustomLabel.qml LiveDataBackground.qml LiveData.qml ModeToggle.qml
    SOURCES FrontendTypes.h
    RESOURCES fonts/fonts.txt images/arrow_left.png images/arrow_right.png images/assist.png images/battery.png images/bike-rearwheel.png images/blue_circle_gps_area.png images/calories.png images/curtain_shadow_handle.png images/info.png images/info_selected.png images/lights_off.png images/lights_on.png images/list.png images/list_selected.png images/map_locate.png images/map_location_arrow.png images/map_zoomin.png images/map_zoomout.png images/nav_nodir.png images/search_cancel.png images/settings.png images/settings_selected.png images/small_speedometer_shadow.png images/speed.png images/top_curtain_drag.png images/top_curtain_drag_back.png images/trip.png images/sma.png images/ema.png images/raw.png
    SOURCES I_Sensor.h
)


source_group("Source Files// Sensor" FILES sensorsimulator.h sensorsimulator.cpp I_Sensor.h)
source_group("Source Files// Data Structures" FILES circularbuffer.h circularbuffer.cpp buffersubscription.h buffersubscription.cpp I_Subscriber.h)
source_group("Source Files// Data" FILES databuffermanager.h databuffermanager.cpp)
source_group("Source Files// Averager" FILES I_Averager.h smaaverager.h smaaverager.cpp emaaverager.h emaaverager.cpp)
source_group("Source Files// Backend Frontend Interface" FILES I_FrontendAPI.h livedataapi.h livedataapi.cpp trenddataapi.h trenddataapi.cpp )
source_group("Source Files// Utils" FILES types.h FrontendTypes.h)
source_group("QML " FILES main.qml LiveData.qml LiveDataBackground.qml LiveDataMeter.qml )
source_group("QML// Components // Arcs" FILES ArcItem.qml ArcLeft.qml ArcRight.qml CircleIndicator.qml)
source_group("QML// Components " FILES CustomLabel.qml ModeToggle.qml)



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
