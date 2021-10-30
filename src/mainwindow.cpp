#include "mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent, Qt::FramelessWindowHint)
{
    location_forecast = new LocationForecast(this);
    //location_forecast->hide();

    connect(location_forecast, &LocationForecast::modelChanged,
        this, &MainWindow::onLocationModelChanged);
    locations_manager = LocationsManager::getInstance(this, location_forecast);
    setMinimumHeight(600);
    setMinimumWidth(1100);
    //resize(1100, 600);
    auto main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    setLayout(main_layout);

    control_frame = new QFrame;
    auto control_layout = new QHBoxLayout;
    control_layout->setContentsMargins(0, 0, 0, 0);
    control_layout->setSpacing(0);
    control_frame->setLayout(control_layout);
    control_frame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    add_btn = new QPushButton;
    add_btn->setIconSize(QSize(18, 18));
    add_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.5);
    connect(add_btn, &QPushButton::clicked,
        this, &MainWindow::openNewLocationDialog);

    settings_btn = new QPushButton;
    settings_btn->setIconSize(QSize(18, 18));
    settings_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.5);
    connect(settings_btn, &QPushButton::clicked,
        this, &MainWindow::openSettingsDialog);

    auto about_btn = new AnimatedButton("TeamForecast", ROLE::SECONDARY, 0);
    about_btn->setFixedHeight(add_btn->sizeHint().height() * 1.5);
    connect(about_btn, &AnimatedButton::clicked,
        this, &MainWindow::openAboutDialog);

    switch_btn = new QPushButton;
    switch_btn->setIconSize(QSize(18, 18));
    switch_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.5);
    connect(switch_btn,
        &QPushButton::clicked,
        this,
        [&]() {
            switch_btn->setEnabled(false);

            if (dark_theme_enabled)
                setLightTheme();
            else
                setDarkTheme();

            switch_btn->setEnabled(true);
        });

    locations_btn = new AnimatedButton("Менеджер локаций", ROLE::SECONDARY, 0);
    locations_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.5);
    connect(locations_btn, &AnimatedButton::clicked,
        this, &MainWindow::openLocationManager);

    collapse_btn = new QPushButton;
    collapse_btn->setIconSize(QSize(18, 18));
    collapse_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.5);
    connect(collapse_btn, &QPushButton::clicked,
        this, &QWidget::showMinimized);

    close_btn = new QPushButton;
    close_btn->setIconSize(QSize(18, 18));
    close_btn->setMinimumHeight(add_btn->sizeHint().height() * 1.5);
    connect(close_btn, &QPushButton::clicked,
        qApp, &QApplication::quit);

    control_layout->addWidget(about_btn, 4);
    control_layout->addWidget(switch_btn, 1);
    control_layout->addWidget(add_btn, 1);
    control_layout->addWidget(locations_btn, 9);
    control_layout->addStretch(3);
    control_layout->addWidget(settings_btn, 1);
    control_layout->addWidget(collapse_btn, 1);
    control_layout->addWidget(close_btn, 1);

    hint_widget_ = new HintWidget(this);
    hint_widget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    main_layout->addWidget(control_frame, 0, Qt::AlignTop);
    main_layout->addWidget(location_forecast);
    main_layout->addWidget(hint_widget_);

    restoreAll();
    location_forecast->hide();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onLocationModelChanged(LocationModel* model)
{
    if (model) {
        if (location_forecast->isHidden()) {
            location_forecast->show();
            hint_widget_->hide();
        }
        locations_btn->setText(model->label());
    } else {
        location_forecast->hide();
        hint_widget_->show();
    }
}

void MainWindow::openAboutDialog()
{
    AboutDialog* d;
    if (location_forecast->isVisible())
        d = new AboutDialog(this, location_forecast);
    else
        d = new AboutDialog(this, hint_widget_);
    d->open();
}

void MainWindow::openSettingsDialog()
{
    SettingsDialog* d;
    if (location_forecast->isVisible())
        d = new SettingsDialog(this, location_forecast);
    else
        d = new SettingsDialog(this, hint_widget_);
    d->open();
}

void MainWindow::openNewLocationDialog()
{
    NewLocationDialog* d;
    if (location_forecast->isVisible())
        d = new NewLocationDialog(this, locations_manager, location_forecast);
    else
        d = new NewLocationDialog(this, locations_manager, hint_widget_);
    d->open();
}

void MainWindow::openLocationManager()
{
    if (location_forecast->isVisible())
        location_manager_view = LocationsManagerView::create(this,
            locations_manager,
            location_forecast);
    else
        location_manager_view = LocationsManagerView::create(this,
            locations_manager,
            hint_widget_);
    location_manager_view->setFixedSize(locations_btn->width(), control_frame->height() * 9);
    location_manager_view->show();
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
                  "QRadioButton {font: 12px; color: black }"
                  "QRadioButton::indicator { height: 16px; width: 16px }"
                  "QRadioButton::indicator::unchecked { image: url(:/icons/radio_unchecked_light) }"
                  "QRadioButton::indicator::checked { image: url(:/icons/radio_checked_light) }"
                  "QRadioButton#favorite_checkbox::indicator { height: 20px; width: 20px}"
                  "QRadioButton#favorite_checkbox::indicator:checked {image: url(:/icons/favorite_checked)}"
                  "QRadioButton#favorite_checkbox::indicator:unchecked {image: url(:/icons/favorite_unchecked)}"
                  "LocationsManagerView > QLineEdit {background: #E0E0E0; color: black;}"
                  "LocationForecast QPushButton { background: rgb(255, 171, 64);font: bold 14px; border-radius: 12px }"
                  "LocationForecast QPushButton::hover { background-color: rgb(255, 152, 0) }"
                  "QLabel#title_label { background: red; color: black; font: bold 20px}"
                  "QLabel#val_label { font: 14px }"
                  "QLabel#last_update_time {font: bold 14px}");

    settings_btn->setIcon(QIcon(":/icons/settings_light"));
    switch_btn->setIcon(QIcon(":/icons/app_switch_theme_light"));
    add_btn->setIcon(QIcon(":/icons/add_light"));
    collapse_btn->setIcon(QIcon(":/icons/app_minimize_light"));
    close_btn->setIcon(QIcon(":/icons/app_close_light"));

    AppStyle::setTheme("default_day");
    dark_theme_enabled = false;
    repaint();
}

void MainWindow::setDarkTheme()
{
    setStyleSheet("* { border: 0px; padding: 0px }"
                  "QSlider::groove:horizontal { background: transparent; height: 4px; position: absolute; right: 0px}"
                  "QSlider::handle:horizontal {width: 12; height: 12px; image: url(:/icons/slider_handle_dark); margin-top: -8px; margin-bottom: -8px;margin-left: 0px; margin-right: 0px; }"
                  "QSlider::add-page:horizontal { background: rgba(255, 255, 255, 120);}"
                  "QSlider::sub-page:horizontal {background: white;}"
                  "QPushButton { background: rgb(55, 71, 79); color: white; font: 14px }"
                  "QPushButton::hover { background-color: #2d3940 }"
                  "QFrame > PushButton { background: rgb(55, 71, 79); color: white; font: 14px }"
                  "QFrame > QPushButton::hover { background-color: #2d3940 }"
                  "QGroupBox {font-size: 14px; color: white }"
                  "QRadioButton {font: 12px; color: white }"
                  "QRadioButton::indicator { height: 16px; width: 16px }"
                  "QRadioButton::indicator::unchecked { image: url(:/icons/radio_unchecked_dark) }"
                  "QRadioButton::indicator::checked { image: url(:/icons/radio_checked_dark) }"
                  "QRadioButton#favorite_checkbox::indicator { height: 20px; width: 20px}"
                  "QRadioButton#favorite_checkbox::indicator:checked {image: url(:/icons/favorite_checked)}"
                  "QRadioButton#favorite_checkbox::indicator:unchecked {image: url(:/icons/favorite_unchecked)}"
                  "LocationsManagerView > QLineEdit {background: #2d3940; color: white;}"
                  "LocationForecast QWidget { color: white; }"
                  "LocationForecast QPushButton {font: bold 14px; background-color: rgb(1, 87, 155); border-radius: 12px}"
                  "LocationForecast QPushButton::hover {background: rgb(1, 75,133) }"
                  "QLabel#title_label {background: rgb(55, 71, 79); color: white; font: bold 20px }"
                  "QLabel#val_label { font: 14px }"
                  "QLabel#last_update_time {font: bold 14px}");

    settings_btn->setIcon(QIcon(":/icons/settings_dark"));
    switch_btn->setIcon(QIcon(":/icons/app_switch_theme_dark"));
    add_btn->setIcon(QIcon(":/icons/add_dark"));
    collapse_btn->setIcon(QIcon(":/icons/app_minimize_dark"));
    close_btn->setIcon(QIcon(":/icons/app_close_dark"));

    AppStyle::setTheme("default_night");
    dark_theme_enabled = true;
    repaint();
}

void MainWindow::restoreAll()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
        "TeamForecast", "TeamForecast");

    if (bool dark_mode = settings.value("dark_by_default").toBool(); dark_mode == true)
        setDarkTheme();
    else
        setLightTheme();

    if (int save_mode = settings.value("save_mode").toInt(); save_mode == 1 || save_mode == 2)
        restoreLocations();
    /*
    locations_manager->setUpdateInterval(
                settings.value("update_interval").toInt()); */
}

void MainWindow::restoreLocations()
{
    QString app_roaming_storage = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile locations_list(app_roaming_storage + "/locations_list.json");
    locations_list.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument json_temporary = QJsonDocument::fromJson(locations_list.readAll());
    locations_list.close();

    auto locations_array = json_temporary.toVariant().toList();
    for (auto& each : locations_array) {
        auto each_location = each.toMap();
        auto new_location = new LocationForecast(each_location["lat"].toString(), each_location["lon"].toString());
        new_location->setFavorite(each_location["is_favorite"].toBool());
    }
}

void MainWindow::saveLocations(bool only_favorite)
{ /*
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
*/
}

void MainWindow::closeEvent(QCloseEvent* event)
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

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    /*
    if (auto lmv = location_manager_view; lmv != nullptr
        && !lmv->rect().contains(mapToGlobal(event->pos())) && lmv->isVisible()) {
        lmv->deleteLater();
        location_manager_view = nullptr;
    }*/
    QWidget::mousePressEvent(event);
}
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event); /*
    if (moving_in_move_area)
        move(mapToGlobal(event->pos()) - offset);*/
}
void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    moving_in_move_area = false;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(AppStyle::backgroundColor(ROLE::SECONDARY, STATE::NORMAL)));
    painter.setPen(Qt::NoPen);

    painter.drawRect(rect());
    /*
    if (location_forecast->isHidden() && location_forecast->isEnabled()) {
       painter.setPen(AppStyle::textPrimaryColor());
       if (add_btn) {
           auto ab_rect = add_btn->geometry();
           painter.drawLine(ab_rect.center().x(),
                            ab_rect.bottom(),
                            ab_rect.center().x() - rect().width() / 16,
                            ab_rect.bottom() + rect().height() / 6);

           QString add_str("Добавьте локацию");
           painter.drawText(ab_rect.center().x() - rect().width() / 16 - 16,
                            ab_rect.bottom() + rect().height() / 6 + 16,
                            add_str);
       }
       if (locations_btn && locations_manager && locations_manager->count()) {
           auto lb_rect = locations_btn->geometry();
           painter.drawLine(lb_rect.center().x(),
                            lb_rect.bottom(),
                            lb_rect.center().x() + rect().width() / 8,
                            lb_rect.bottom() + rect().height() / 8);

           QString ch_str("Или выберите из существующих");
           painter.drawText(lb_rect.center().x() + rect().width() / 8 - 16,
                            lb_rect.bottom() + rect().height() / 8 + 16,
                            ch_str);
       }
    }*/
}
