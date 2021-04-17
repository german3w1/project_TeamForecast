#include "mainwindow.h"
#include "locationforecast.h"
#include <aboutdialog.h>
#include <newlocationdialog.h>
#include <darkoverlayeffect.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
{

    setLightTheme();
    setMinimumHeight(600);
    setMinimumWidth(1100);
    //resize(1100, 600);
    auto main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->setSpacing(0);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    setLayout(main_layout);

    locations = new QTabWidget;
    locations->setMovable(true);
    locations->setTabsClosable(true);
    locations->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    connect(locations, &QTabWidget::tabCloseRequested, this, &MainWindow::deleteLocationRequest);

    locations->setStyleSheet("QTabBar {padding: 0px; margin: 0px }"
                             "QTabBar::close-button {image: url(:/icons/close);}"
                             "QTabWidget::pane {background: transparent}"
                             "QTabBar::close-button:hover {image: url(:/icons/close_hover);}");

    auto control_frame = new QFrame;
    auto control_layout = new QHBoxLayout;
    control_layout->setContentsMargins(0, 0, 0, 0);
    control_layout->setSpacing(0);
    control_frame->setLayout(control_layout);
    control_frame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    add_btn = new QPushButton;
    //add_btn->setText("Добавить локацию");
    add_btn->setIconSize(QSize(18, 18));
    add_btn->setIcon(QIcon(":/icons/add_dark"));
    add_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.4);
    connect(add_btn, &QPushButton::clicked, this, &MainWindow::newLocationRequest);

    auto about_btn = new QPushButton("TeamForecast");
    about_btn->setFixedHeight(add_btn->sizeHint().height() * 1.4);
    connect(about_btn, &QPushButton::clicked, this, &MainWindow::aboutRequest);

    switch_btn = new QPushButton;
    switch_btn->setIconSize(QSize(18, 18));
    switch_btn->setIcon(QIcon(":/icons/app_switch_theme_dark"));
    switch_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.4);
    connect(switch_btn, &QPushButton::clicked, this, &MainWindow::changeThemeRequest);

    collapse_btn = new QPushButton;
    collapse_btn->setIconSize(QSize(18, 18));
    collapse_btn->setIcon(QIcon(":/icons/app_minimize_dark"));
    collapse_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.4);
    connect(collapse_btn, &QPushButton::clicked, this, &QWidget::showMinimized);

    close_btn = new QPushButton();
    close_btn->setIconSize(QSize(18, 18));
    close_btn->setIcon(QIcon(":/icons/app_close_dark"));
    close_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.4);
    connect(close_btn, &QPushButton::clicked, qApp, &QApplication::quit);

    control_layout->addWidget(about_btn, 4);
    control_layout->addWidget(switch_btn, 1);
    control_layout->addWidget(add_btn, 1);
    control_layout->addWidget(new QLabel, 13);
    control_layout->addWidget(collapse_btn, 1);
    control_layout->addWidget(close_btn, 1);


    dark_theme_enabled = false;
    main_layout->addWidget(control_frame);
    main_layout->addWidget(locations);

}

MainWindow::~MainWindow()
{

}

void MainWindow::changeThemeRequest() {
    switch_btn->setEnabled(false);

    dark_theme_enabled = !dark_theme_enabled;
    if (dark_theme_enabled){
        setDarkTheme();
        switch_btn->setIcon(QIcon(":/icons/app_switch_theme_light"));
        add_btn->setIcon(QIcon(":/icons/add_light"));
        collapse_btn->setIcon(QIcon(":/icons/app_minimize_light"));
        close_btn->setIcon(QIcon(":/icons/app_close_light"));
    }
    else {
        setLightTheme();
        switch_btn->setIcon(QIcon(":/icons/app_switch_theme_dark"));
        add_btn->setIcon(QIcon(":/icons/add_dark"));
        collapse_btn->setIcon(QIcon(":/icons/app_minimize_dark"));
        close_btn->setIcon(QIcon(":/icons/app_close_dark"));
    }
    switch_btn->setEnabled(true);
}

void MainWindow::setLightTheme()
{
    setStyleSheet("* { border: 0px; padding: 0px}"
                  "QPushButton { background: white; color: black; font: 14px;}"
                  "QPushButton::hover { background-color: #E0E0E0 }"
                  "MainWindow > QFrame {background-color: white}"
                  "QDialog { background: white }"
                  "QDialog QLabel { font: bold 12px; color: #757575; }"
                  "BasicLocationDialog QLabel { font: bold 12px; color: #757575; }"
                  "BasicLocationDialog QLineEdit { background: transparent; border-bottom: 2px solid #E0E0E0; color:#757575; selection-background-color: #E0E0E0; selection-color: black; }"
                  "BasicLocationDialog QPushButton { font: bold 14px; border-radius: 16px }"
                  "BasicLocationDialog QPushButton::hover { background-color: #E0E0E0 }"
                  "LocationForecast QWidget { color: white; }"
                  "LocationForecast { background: white; border-radius: 0px }"
                  "QFrame#control_panel_frame {background: rgb(255, 171, 64); border-radius: 12px}"
                  "LocationForecast QPushButton { background: rgb(255, 171, 64);font: bold 14px; border-radius: 12px }"
                  "LocationForecast QPushButton::hover { background-color: rgb(255, 152, 0) }"
                  "QFrame#forecast_frame { background: white }"
                  "QFrame#scroll_frame { background: white}"
                  "ExpandingWeatherWidget {background: rgb(255, 171, 64); border-radius: 12px}"
                  "QLabel#title_label { background: white; color: black; font: bold 20px}"
                  "QLabel#val_label { font: 14px }"
                  "QLabel#last_update_time {font: bold 14px}");
}

void MainWindow::setDarkTheme()
{
    setStyleSheet("* { border: 0px; padding: 0px }"
                  "QStackedWidget#qt_tabwidget_stackedwidget {background: rgb(55, 71, 79)}"
                  "QPushButton { background: rgb(55, 71, 79); color: white; font: 14px }"
                  "QPushButton::hover { background-color: #2d3940 }"
                  "MainWindow > QFrame {background-color: rgb(55, 71, 79)}"
                  "QFrame > PushButton { background: rgb(55, 71, 79); color: white; font: 14px }"
                  "QFrame > QPushButton::hover { background-color: #2d3940 }"
                  "QDialog { background: rgb(55, 71, 79); }"
                  "QDialog QLabel {font: bold 12px; color: white}"
                  "BasicLocationDialog QLabel { font: bold 12px; color: white; }"
                  "BasicLocationDialog QLineEdit { background: transparent; border-bottom: 2px solid #E0E0E0; color: white; selection-background-color: #E0E0E0; selection-color: black;}"
                  "BasicLocationDialog QPushButton { font: bold 14px; border-radius: 16px }"
                  "BasicLocationDialog QPushButton::hover { background-color: #2d3940 }"
                  "LocationForecast QWidget { color: white;  }"
                  "LocationForecast { background: rgb(55, 71, 79); border-radius: 0px }"
                  "LocationForecast QPushButton {font: bold 14px; background-color: rgb(1, 87, 155); border-radius: 12px}"
                  "LocationForecast QPushButton::hover {background: rgb(1, 75,133) }"
                  "QFrame#control_panel_frame {background-color: rgb(1, 87, 155); border-radius: 12px}"
                  "QFrame#forecast_frame {background: rgb(55, 71, 79) }"
                  "QFrame#scroll_frame {background: rgb(55, 71, 79)}"
                  "QLabel#title_label {background: rgb(55, 71, 79); color: white; font: bold 20px }"
                  "QLabel#val_label { font: 14px }"
                  "QLabel#last_update_time {font: bold 14px}"
                  "ExpandingWeatherWidget {background: rgb(1, 87, 155); border-radius: 12px}");
}

void MainWindow::newLocationRequest(){
    NewLocationDialog(this, locations);
}

void MainWindow::aboutRequest() {
    setGraphicsEffect(new DarkOverlayEffect);
    AboutDialog(this);
    delete graphicsEffect();
}

void MainWindow::deleteLocationRequest(int index){
   locations->widget(index)->deleteLater();
}
