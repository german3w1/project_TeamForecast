QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    basiclocationdialog.cpp \
    currentwidget.cpp \
    dailywidget.cpp \
    darkoverlayeffect.cpp \
    editlocationdialog.cpp \
    expandingweatherwidget.cpp \
    hourlywidget.cpp \
    locationforecast.cpp \
    main.cpp \
    mainwindow.cpp \
    newlocationdialog.cpp \
    scrollareawrapper.cpp \
    weathertools.cpp

HEADERS += \
    aboutdialog.h \
    basiclocationdialog.h \
    currentwidget.h \
    dailywidget.h \
    darkoverlayeffect.h \
    editlocationdialog.h \
    expandingweatherwidget.h \
    hourlywidget.h \
    locationforecast.h \
    mainwindow.h \
    newlocationdialog.h \
    scrollareawrapper.h \
    weathertools.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc


