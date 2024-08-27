cmake_minimum_required(VERSION 3.16)

set(QT_ENABLE_VERBOSE_DEPLOYMENT TRUE)

project(BreathTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(${CMAKE_SOURCE_DIR}/inc)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

# Source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "inc/*.h")

# QML files
file(GLOB QML_FILES "qml/*.qml")

# Add executable with Qt
qt_add_executable(appBreathTracker
    ${SOURCES}
    ${HEADERS}
)

# Qt Add QML Module
qt_add_qml_module(appBreathTracker
    URI BreathTracker
    VERSION 1.0
    # QML Files
    QML_FILES
    qml/main.qml
    qml/DataTrends.qml
    qml/ArcItem.qml
    qml/ArcLeft.qml
    qml/ArcRight.qml
    qml/CircleIndicator.qml
    qml/CustomLabel.qml
    qml/LiveDataBackground.qml
    qml/LiveData.qml
    qml/ModeToggle.qml
    qml/SettingsDrawer.qml
    qml/SettingsSection.qml

    # Source Files
    SOURCES
    src/sensorsimulator.cpp
    src/circularbuffer.cpp
    src/buffersubscription.cpp
    src/databuffermanager.cpp
    src/smaaverager.cpp
    src/emaaverager.cpp
    src/livedataapi.cpp
    src/trenddataapi.cpp

    # Header Files
    SOURCES
    inc/sensorsimulator.h
    inc/circularbuffer.h
    inc/buffersubscription.h
    inc/databuffermanager.h
    inc/I_Averager.h
    inc/smaaverager.h
    inc/I_Subscriber.h
    inc/emaaverager.h
    inc/types.h
    inc/I_FrontendAPI.h
    inc/livedataapi.h
    inc/trenddataapi.h
    inc/FrontendTypes.h
    inc/I_Sensor.h
    inc/sensorfactory.h

    # Resources (if any)
    RESOURCES
    resources/fonts/fonts.txt
    resources/images/arrow_left.png
    resources/images/arrow_right.png
    resources/images/assist.png
    resources/images/battery.png
    resources/images/bike-rearwheel.png
    resources/images/blue_circle_gps_area.png
    resources/images/calories.png
    resources/images/curtain_shadow_handle.png
    resources/images/info.png
    resources/images/info_selected.png
    resources/images/lights_off.png
    resources/images/lights_on.png
    resources/images/list.png
    resources/images/list_selected.png
    resources/images/map_locate.png
    resources/images/map_location_arrow.png
    resources/images/map_zoomin.png
    resources/images/map_zoomout.png
    resources/images/nav_nodir.png
    resources/images/search_cancel.png
    resources/images/settings.png
    resources/images/settings_selected.png
    resources/images/small_speedometer_shadow.png
    resources/images/speed.png
    resources/images/top_curtain_drag.png
    resources/images/top_curtain_drag_back.png
    resources/images/trip.png
    resources/images/sma.png
    resources/images/ema.png
    resources/images/raw.png
)


# source_group("Source Files// Sensor" FILES sensorsimulator.h sensorsimulator.cpp I_Sensor.h sensorfactory.h)
# source_group("Source Files// Data Structures" FILES circularbuffer.h circularbuffer.cpp buffersubscription.h buffersubscription.cpp I_Subscriber.h)
# source_group("Source Files// Data" FILES databuffermanager.h databuffermanager.cpp)
# source_group("Source Files// Averager" FILES I_Averager.h smaaverager.h smaaverager.cpp emaaverager.h emaaverager.cpp)
# source_group("Source Files// Backend Frontend Interface" FILES I_FrontendAPI.h livedataapi.h livedataapi.cpp trenddataapi.h trenddataapi.cpp )
# source_group("Source Files// Utils" FILES types.h FrontendTypes.h)
# source_group("QML " FILES main.qml LiveData.qml LiveDataBackground.qml LiveDataMeter.qml )
# source_group("QML// Components // Arcs" FILES ArcItem.qml ArcLeft.qml ArcRight.qml CircleIndicator.qml)
# source_group("QML// Components " FILES CustomLabel.qml ModeToggle.qml)



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
