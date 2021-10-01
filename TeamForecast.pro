QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base/animatedbutton.cpp \
    base/animatedwidget.cpp \
    base/textwidget.cpp \
    dialogs/aboutdialog.cpp \
    hintwidget.cpp \
    models/abstractweathermodel.cpp \
    base/appstyle.cpp \
    dialogs/basiclocationdialog.cpp \
    models/currentmodel.cpp \
    views/currentwidget.cpp \
    models/dailymodel.cpp \
    views/dailywidget.cpp \
    darkoverlayeffect.cpp \
    dialogs/editlocationdialog.cpp \
    views/expandingweatherwidget.cpp \
    models/hourlymodel.cpp \
    views/hourlywidget.cpp \
    views/locationforecast.cpp \
    views/locationminiview.cpp \
    models/locationmodel.cpp \
    models/locationsmanager.cpp \
    dialogs/locationsmanagerview.cpp \
    main.cpp \
    mainwindow.cpp \
    dialogs/newlocationdialog.cpp \
    dialogs/roundeddialog.cpp \
    roundedmenu.cpp \
    base/scrollareawrapper.cpp \
    dialogs/settingsdialog.cpp

HEADERS += \
    base/animatedbutton.h \
    base/animatedwidget.h \
    base/textwidget.h \
    dialogs/aboutdialog.h \
    hintwidget.h \
    models/abstractweathermodel.h \
    base/appstyle.h \
    dialogs/basiclocationdialog.h \
    models/currentmodel.h \
    views/currentwidget.h \
    models/dailymodel.h \
    views/dailywidget.h \
    darkoverlayeffect.h \
    dialogs/editlocationdialog.h \
    views/expandingweatherwidget.h \
    models/hourlymodel.h \
    views/hourlywidget.h \
    views/locationforecast.h \
    views/locationminiview.h \
    models/locationmodel.h \
    models/locationsmanager.h \
    dialogs/locationsmanagerview.h \
    mainwindow.h \
    dialogs/newlocationdialog.h \
    dialogs/roundeddialog.h \
    roundedmenu.h \
    base/scrollareawrapper.h \
    dialogs/settingsdialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc


