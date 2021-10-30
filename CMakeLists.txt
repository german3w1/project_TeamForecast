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
    src/base/basewidget.cpp
    src/base/animatedbutton.cpp
    src/base/animatedwidget.cpp
    src/base/textwidget.cpp
    src/base/appstyle.cpp
    src/base/scrollareawrapper.cpp
    src/dialogs/editlocationdialog.cpp
    src/dialogs/aboutdialog.cpp
    src/dialogs/basiclocationdialog.cpp
    src/dialogs/newlocationdialog.cpp
    src/dialogs/roundeddialog.cpp
    src/dialogs/settingsdialog.cpp
    src/dialogs/locationsmanagerview.cpp
    src/models/abstractweathermodel.cpp 
    src/models/currentmodel.cpp
    src/models/hourlymodel.cpp
    src/models/dailymodel.cpp
    src/models/locationmodel.cpp
    src/models/locationsmanager.cpp
    src/views/currentwidget.cpp
    src/views/dailywidget.cpp
    src/views/expandingweatherwidget.cpp    
    src/views/hourlywidget.cpp
    src/views/locationforecast.cpp
    src/views/locationminiview.cpp
    src/notifications/notificationsystem.cpp
    src/main.cpp
    src/darkoverlayeffect.cpp
    src/mainwindow.cpp
    src/hintwidget.cpp
    src/roundedmenu.cpp  
)

set(HEADERS 
    src/base/basewidget.h
    src/base/animatedbutton.h
    src/base/animatedwidget.h
    src/base/textwidget.h
    src/base/appstyle.h
    src/base/scrollareawrapper.h
    src/dialogs/editlocationdialog.h
    src/dialogs/aboutdialog.h
    src/dialogs/basiclocationdialog.h
    src/dialogs/newlocationdialog.h
    src/dialogs/roundeddialog.h
    src/dialogs/settingsdialog.h
    src/dialogs/locationsmanagerview.h
    src/models/abstractweathermodel.h
    src/models/currentmodel.h
    src/models/hourlymodel.h
    src/models/dailymodel.h
    src/models/locationmodel.h
    src/models/locationsmanager.h
    src/views/currentwidget.h
    src/views/dailywidget.h
    src/views/expandingweatherwidget.h
    src/views/hourlywidget.h
    src/views/locationforecast.h
    src/views/locationminiview.h
    src/notifications/notificationsystem.h
    src/darkoverlayeffect.h
    src/mainwindow.h
    src/hintwidget.h
    src/roundedmenu.h
)

set(RESOURCES src/resources.qrc)

add_executable(TeamForecast ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(TeamForecast PRIVATE Qt6::Network Qt6::Gui Qt6::Core Qt6::Widgets)
