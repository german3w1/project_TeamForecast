cmake_minimum_required(VERSION 3.1.0)

project(TeamForecast VERSION 2.0.3 LANGUAGES CXX)

#it's required to hide app console window behind gui when app starts outside the IDE(only windows)
if (${CMAKE_SYSTEM} MATCHES "Windows")
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

set(CMAKE_CXX_STANDART 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Gui Widgets Network Core REQUIRED)

set(SOURCES 
    base/animatedbutton.cpp
    base/animatedwidget.cpp
    base/textwidget.cpp
    dialogs/aboutdialog.cpp
    hintwidget.cpp
    models/abstractweathermodel.cpp
    base/appstyle.cpp
    dialogs/basiclocationdialog.cpp
    models/currentmodel.cpp
    views/currentwidget.cpp
    models/dailymodel.cpp
    views/dailywidget.cpp
    darkoverlayeffect.cpp
    dialogs/editlocationdialog.cpp
    views/expandingweatherwidget.cpp
    models/hourlymodel.cpp
    views/hourlywidget.cpp
    views/locationforecast.cpp
    views/locationminiview.cpp
    models/locationmodel.cpp
    models/locationsmanager.cpp
    dialogs/locationsmanagerview.cpp
    main.cpp
    mainwindow.cpp
    dialogs/newlocationdialog.cpp
    dialogs/roundeddialog.cpp
    roundedmenu.cpp
    base/scrollareawrapper.cpp
    dialogs/settingsdialog.cpp
)

set(HEADERS 
    base/animatedbutton.cpp
    base/animatedwidget.h
    base/textwidget.h
    dialogs/aboutdialog.h
    hintwidget.h
    models/abstractweathermodel.h
    base/appstyle.h
    dialogs/basiclocationdialog.h
    models/currentmodel.h
    views/currentwidget.h
    models/dailymodel.h
    views/dailywidget.h
    darkoverlayeffect.h
    dialogs/editlocationdialog.h
    views/expandingweatherwidget.h
    models/hourlymodel.h
    views/hourlywidget.h
    views/locationforecast.h
    views/locationminiview.h
    models/locationmodel.h
    models/locationsmanager.h
    dialogs/locationsmanagerview.h
    mainwindow.h
    dialogs/newlocationdialog.h
    dialogs/roundeddialog.h
    roundedmenu.h
    base/scrollareawrapper.h
    dialogs/settingsdialog.h
)

set(RESOURCES resources.qrc)

add_executable(TeamForecast ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(TeamForecast PRIVATE Qt6::Network Qt6::Gui Qt6::Core Qt6::Widgets)
