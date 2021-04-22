#include "mainwindow.h"
#include "locationforecast.h"
#include <aboutdialog.h>
#include <settingsdialog.h>
#include <newlocationdialog.h>
#include <darkoverlayeffect.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent, Qt::FramelessWindowHint)
{
    setMinimumHeight(600);
    setMinimumWidth(1100);
    //resize(1100, 600);
    auto main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->setSpacing(0);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    setLayout(main_layout);

    auto control_frame = new QFrame;
    auto control_layout = new QHBoxLayout;
    control_layout->setContentsMargins(0, 0, 0, 0);
    control_layout->setSpacing(0);
    control_frame->setLayout(control_layout);
    control_frame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    add_btn = new QPushButton;
    add_btn->setIconSize(QSize(18, 18));
    add_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.4);
    connect(add_btn, &QPushButton::clicked, this, &MainWindow::newLocationRequest);

    settings_btn = new QPushButton;
    settings_btn->setIconSize(QSize(18, 18));
    settings_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.4);
    connect(settings_btn, &QPushButton::clicked, this, &MainWindow::openSettingsRequest);

    auto about_btn = new QPushButton("TeamForecast");
    about_btn->setFixedHeight(add_btn->sizeHint().height() * 1.4);
    connect(about_btn, &QPushButton::clicked, this, &MainWindow::aboutRequest);

    switch_btn = new QPushButton;
    switch_btn->setIconSize(QSize(18, 18));
    switch_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.4);
    connect(switch_btn, &QPushButton::clicked, this, &MainWindow::changeThemeRequest);

    move_area = new QLabel;

    collapse_btn = new QPushButton;
    collapse_btn->setIconSize(QSize(18, 18));
    collapse_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.4);
    connect(collapse_btn, &QPushButton::clicked, this, &QWidget::showMinimized);


    close_btn = new QPushButton();
    close_btn->setIconSize(QSize(18, 18));
    close_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.4);
    connect(close_btn, &QPushButton::clicked, qApp, &QApplication::quit);

    control_layout->addWidget(about_btn, 4);

    control_layout->addWidget(switch_btn, 1);
    control_layout->addWidget(add_btn, 1);
    control_layout->addWidget(move_area, 12);control_layout->addWidget(settings_btn, 1);
    control_layout->addWidget(collapse_btn, 1);
    control_layout->addWidget(close_btn, 1);

    locations = new QTabWidget;
    locations->setMovable(true);
    locations->setTabsClosable(true);
    locations->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    connect(locations, &QTabWidget::tabCloseRequested, this, &MainWindow::deleteLocationRequest);

    locations->setStyleSheet("QTabBar {padding: 0px; margin: 0px }"
                             "QTabBar::close-button {image: url(:/icons/close);}"
                             "QTabWidget::pane {background: transparent}"
                             "QTabBar::close-button:hover {image: url(:/icons/close_hover);}");

    main_layout->addWidget(control_frame);
    main_layout->addWidget(locations);

    update_timer = new QTimer(this);
    connect(update_timer, &QTimer::timeout, this, &MainWindow::updateWeatherRequest);

    restoreAll();
}

MainWindow::~MainWindow()
{

}

void MainWindow::changeThemeRequest()
{
    switch_btn->setEnabled(false);

    if (dark_theme_enabled) setLightTheme();
    else setDarkTheme();

    switch_btn->setEnabled(true);
}

void MainWindow::setLightTheme()
{
    setStyleSheet("* { border: 0px; padding: 0px}"
                  "QSlider::groove:horizontal { background: transparent; height: 4px; position: absolute; right: 0px}"
                  "QSlider::handle:horizontal {width: 12; height: 12px; image: url(:/icons/slider_handle_light); margin-top: -8px; margin-bottom: -8px;margin-left: 0px; margin-right: 0px; }"
                  "QSlider::add-page:horizontal { background: #E0E0E0;}"
                  "QSlider::sub-page:horizontal {background: black;}"
                  "QPushButton { background: white; color: black; font: 14px;}"
                  "QPushButton::hover { background-color: #E0E0E0 }"
                  "MainWindow > QFrame {background-color: white}"
                  "QDialog { background: white }"
                  "QDialog QLabel { font: bold 12px; color: black; }"
                  "QDialog QPushButton { font: bold 14px; border-radius: 16px }"
                  "QRadioButton {font: 12px; color: black }"
                  "QRadioButton::indicator { height: 16px; width: 16px }"
                  "QRadioButton::indicator::unchecked { image: url(:/icons/radio_unchecked_light) }"
                  "QRadioButton::indicator::checked { image: url(:/icons/radio_checked_light) }"
                  "QRadioButton#favorite_checkbox::indicator { height: 20px; width: 20px}"
                  "QRadioButton#favorite_checkbox::indicator:checked {image: url(:/icons/favorite_checked)}"
                  "QRadioButton#favorite_checkbox::indicator:unchecked {image: url(:/icons/favorite_unchecked)}"
                  "BasicLocationDialog QLabel { font: bold 12px; color: #757575; }"
                  "BasicLocationDialog QLineEdit { background: transparent; border-bottom: 2px solid #E0E0E0; color:#757575; selection-background-color: black; selection-color: white; }"
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

    settings_btn->setIcon(QIcon(":/icons/settings_light"));
    switch_btn->setIcon(QIcon(":/icons/app_switch_theme_light"));
    add_btn->setIcon(QIcon(":/icons/add_light"));
    collapse_btn->setIcon(QIcon(":/icons/app_minimize_light"));
    close_btn->setIcon(QIcon(":/icons/app_close_light"));

    dark_theme_enabled = false;
}

void MainWindow::setDarkTheme()
{
    setStyleSheet("* { border: 0px; padding: 0px }"
                  "QSlider::groove:horizontal { background: transparent; height: 4px; position: absolute; right: 0px}"
                  "QSlider::handle:horizontal {width: 12; height: 12px; image: url(:/icons/slider_handle_dark); margin-top: -8px; margin-bottom: -8px;margin-left: 0px; margin-right: 0px; }"
                  "QSlider::add-page:horizontal { background: rgba(255, 255, 255, 120);}"
                  "QSlider::sub-page:horizontal {background: white;}"
                  "QStackedWidget#qt_tabwidget_stackedwidget {background: rgb(55, 71, 79)}"
                  "QPushButton { background: rgb(55, 71, 79); color: white; font: 14px }"
                  "QPushButton::hover { background-color: #2d3940 }"
                  "MainWindow > QFrame {background-color: rgb(55, 71, 79)}"
                  "QFrame > PushButton { background: rgb(55, 71, 79); color: white; font: 14px }"
                  "QFrame > QPushButton::hover { background-color: #2d3940 }"
                  "QDialog { background: rgb(55, 71, 79); }"
                  "QDialog QLabel {font: bold 12px; color: white}"
                  "QDialog QPushButton { font: bold 14px; border-radius: 16px }"
                  "QGroupBox {font-size: 14px; color: white }"
                  "QRadioButton {font: 12px; color: white }"
                  "QRadioButton::indicator { height: 16px; width: 16px }"
                  "QRadioButton::indicator::unchecked { image: url(:/icons/radio_unchecked_dark) }"
                  "QRadioButton::indicator::checked { image: url(:/icons/radio_checked_dark) }"
                  "QRadioButton#favorite_checkbox::indicator { height: 20px; width: 20px}"
                  "QRadioButton#favorite_checkbox::indicator:checked {image: url(:/icons/favorite_checked)}"
                  "QRadioButton#favorite_checkbox::indicator:unchecked {image: url(:/icons/favorite_unchecked)}"
                  "BasicLocationDialog QLabel { font: bold 12px; color: white; }"
                  "BasicLocationDialog QLineEdit { background: transparent; border-bottom: 2px solid #E0E0E0; color: white; selection-background-color: white; selection-color: black }"
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

    settings_btn->setIcon(QIcon(":/icons/settings_dark"));
    switch_btn->setIcon(QIcon(":/icons/app_switch_theme_dark"));
    add_btn->setIcon(QIcon(":/icons/add_dark"));
    collapse_btn->setIcon(QIcon(":/icons/app_minimize_dark"));
    close_btn->setIcon(QIcon(":/icons/app_close_dark"));

    dark_theme_enabled = true;
}

void MainWindow::newLocationRequest()
{
    setGraphicsEffect(new DarkOverlayEffect);
    NewLocationDialog(this, locations);
    delete graphicsEffect();
}

void MainWindow::aboutRequest()
{
    setGraphicsEffect(new DarkOverlayEffect);
    AboutDialog(this);
    delete graphicsEffect();
}

void MainWindow::deleteLocationRequest(int index)
{
   locations->widget(index)->deleteLater();
}

void MainWindow::updateWeatherRequest()
{
    auto n = locations->count();
    for (auto i = 0; i < n; i++)
        qobject_cast<LocationForecast*>(locations->widget(i))->weatherUpdateRequested();
}

void MainWindow::openSettingsRequest()
{
    setGraphicsEffect(new DarkOverlayEffect);
    SettingsDialog(this);
    delete graphicsEffect();
}

void MainWindow::restoreAll()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TeamForecast", "TeamForecast");

    if (bool dark_mode = settings.value("dark_by_default").toBool(); dark_mode == true)
        setDarkTheme();
    else
        setLightTheme();

    if (int save_mode = settings.value("save_mode").toInt(); save_mode == 1 || save_mode == 2)
        restoreLocations();
}

void MainWindow::restoreLocations()
{
    QString app_roaming_storage = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile locations_list(app_roaming_storage + "/locations_list.json");
    locations_list.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument json_temporary =  QJsonDocument::fromJson(locations_list.readAll());
    locations_list.close();

    auto locations_array =  json_temporary.toVariant().toList();
    for (auto &each : locations_array) {
        auto each_location = each.toMap();
        //qDebug() << each_location["lat"].toString() << each_location["lon"].toString() << each_location["name"].toString();
        auto new_location = new LocationForecast(each_location["lat"].toString(), each_location["lon"].toString());
        new_location->setFavorite(each_location["is_favorite"].toBool());
        locations->addTab(new_location, each_location["name"].toString());
    }

}

void MainWindow::saveLocations(bool only_favorite)
{
    auto n = locations->count();
    QJsonArray locations_array;
    if (only_favorite)
        for (auto i = 0; i < n; i++) {
            auto each = qobject_cast<LocationForecast*>(locations->widget(i));
            if (each->isFavorite()) {
                QJsonObject json_object;
                json_object.insert("name", locations->tabText(i));
                json_object.insert("lat", each->getLat());
                json_object.insert("lon", each->getLon());
                json_object.insert("is_favorite", each->isFavorite());
                locations_array.push_back(json_object);
            }
        }
    else
        for (auto i = 0; i < n; i++) {
            auto each = qobject_cast<LocationForecast*>(locations->widget(i));
            QJsonObject json_object;
            json_object.insert("name", locations->tabText(i));
            json_object.insert("lat", each->getLat());
            json_object.insert("lon", each->getLon());
            json_object.insert("is_favorite", each->isFavorite());
            locations_array.push_back(json_object);
        }


    QJsonDocument doc(locations_array);
    QString app_roaming_storage = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile locations_list(app_roaming_storage + "/locations_list.json");
    locations_list.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    locations_list.write(doc.toJson());
    locations_list.close();

}


void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TeamForecast", "TeamForecast");
    if (settings.value("remember_theme").toBool() == true)
        settings.setValue("dark_by_default", dark_theme_enabled);

    if (auto save_mode = settings.value("save_mode").toInt(); save_mode == 1)
        saveLocations(false);
    else if (save_mode == 2)
        saveLocations(true);

    QWidget::closeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if ((event->button() == Qt::LeftButton) && move_area->geometry().contains(event->pos())) {
        offset = event->pos();
        moving_in_move_area = true;
    }

}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if (moving_in_move_area)
        move(event->globalPos() - offset);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    moving_in_move_area = false;

}
