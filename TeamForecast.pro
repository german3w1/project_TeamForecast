QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basiclocationdialog.cpp \
    currentforecast.cpp \
    dailyforecast.cpp \
    dailywidget.cpp \
    editlocationdialog.cpp \
    expandingweatherwidget.cpp \
    hourlyforecast.cpp \
    locationforecast.cpp \
    main.cpp \
    mainforecast.cpp \
    mainwindow.cpp \
    newlocationdialog.cpp \
    weathertools.cpp

HEADERS += \
    basiclocationdialog.h \
    currentforecast.h \
    dailyforecast.h \
    dailywidget.h \
    editlocationdialog.h \
    expandingweatherwidget.h \
    hourlyforecast.h \
    locationforecast.h \
    mainforecast.h \
    mainwindow.h \
    newlocationdialog.h \
    weathertools.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc


