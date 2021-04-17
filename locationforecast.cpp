#include "locationforecast.h"
#include <editlocationdialog.h>

LocationForecast::LocationForecast(QWidget* parent) : QFrame(parent)
{
    setContentsMargins(0,0,0,0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto main_layout = new QVBoxLayout;
    setLayout(main_layout);

    control_panel_frame = new QFrame(this);
    control_panel_frame->setContentsMargins(2,0,2,0);
    auto control_panel_layout = new QHBoxLayout;
    control_panel_frame->setLayout(control_panel_layout);
    main_layout->addWidget(control_panel_frame);
    control_panel_frame->setObjectName("control_panel_frame");

    auto edit = new QPushButton;
    edit->setIcon(QIcon(":/icons/edit"));
    edit->setIconSize(QSize(18, 18));
    edit->setMaximumSize(30, 30);
    connect(edit, &QPushButton::clicked, this, &LocationForecast::onEditBtnClicked);
    latitude = new QLabel;
    latitude->setObjectName("val_label");
    longitude = new QLabel;
    longitude->setObjectName("val_label");
    last_update_time = new QLabel("Последнее успешное обновление");
    last_update_time->setObjectName("last_update_time");
    last_update_time_val = new QLabel;
    last_update_time_val->setObjectName("val_label");
    update_btn = new QPushButton("Обновить", control_panel_frame);
    update_btn->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    connect(update_btn, &QPushButton::clicked, this, &LocationForecast::onUpdateBtnClicked);

    control_panel_layout->addWidget(edit, 1);
    control_panel_layout->addWidget(latitude, 1, Qt::AlignCenter);
    control_panel_layout->addWidget(longitude, 1, Qt::AlignCenter);
    control_panel_layout->addWidget(last_update_time, 3, Qt::AlignRight);
    control_panel_layout->addWidget(last_update_time_val, 2, Qt::Alignment(Qt::AlignCenter));
    control_panel_layout->addWidget(update_btn, 1);
    control_panel_frame->setFixedHeight(control_panel_frame->height() + 20);

    forecasts_frame = new QFrame(this);
    forecasts_frame->setContentsMargins(0,0,0,0);
    forecasts_frame->setObjectName("forecast_frame");
    forecasts_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto forecasts_layout = new QHBoxLayout;
    forecasts_frame->setLayout(forecasts_layout);

    auto current_and_hourly = new ScrollAreaWrapper(this);
    auto current_label = new QLabel("Текущая погода");
    current_label->setObjectName("title_label");
    current_widget = new CurrentWidget;

    auto hourly_label = new QLabel("Почасовой прогноз");
    hourly_label->setObjectName("title_label");
    current_and_hourly->scroll_layout->addWidget(current_label, 0, Qt::Alignment(Qt::AlignHCenter));
    current_and_hourly->scroll_layout->addWidget(current_widget);
    current_and_hourly->scroll_layout->addWidget(hourly_label, 0, Qt::Alignment(Qt::AlignHCenter));
    for (auto i = 0; i < 47; i++) {
        hourly_widgets[i] = new HourlyWidget(this);
        current_and_hourly->scroll_layout->addWidget(hourly_widgets[i]);
    }

    auto daily = new ScrollAreaWrapper(this);
    auto daily_label = new QLabel("Прогноз на неделю");
    daily_label->setObjectName("title_label");
    daily->scroll_layout->addWidget(daily_label, 0, Qt::Alignment(Qt::AlignHCenter));
    for (auto i = 0; i < 7; i++) {
        daily_widgets[i] = new DailyWidget;
        daily->scroll_layout->addWidget(daily_widgets[i]);
    }
    forecasts_layout->addWidget(current_and_hourly);
    forecasts_layout->addWidget(daily);
    main_layout->addWidget(forecasts_frame);

    previous_update_failed = false;
    network_manager = new QNetworkAccessManager(this);
    connect(network_manager, &QNetworkAccessManager::finished, this, &LocationForecast::onRequestProcessed);
}

void LocationForecast::init(const QString &lat, const QString &lon) {
    latitude->setText(lat);
    longitude->setText(lon);
    updateWeatherInfo(lat, lon);
}

void LocationForecast::onUpdateBtnClicked(){
    updateWeatherInfo(latitude->text(), longitude->text());
}

void LocationForecast::onEditBtnClicked(){
    bool need_update = false;
    EditLocationDialog(parentWidget()->parentWidget(), qobject_cast<QTabWidget*>(parentWidget()->parentWidget()), need_update);
    if (need_update) updateWeatherInfo(latitude->text(), longitude->text());
}

void LocationForecast::updateWeatherInfo(const QString &lat, const QString &lon){
    update_btn->setEnabled(false);
    update_btn->setText("Обновление");

    QString api_key = "3e69eacb46ce8074001a5562dfb9e38a";
    QString url = "https://api.openweathermap.org/data/2.5/onecall?lat=%1&lon=%2&exclude=minutely,alerts&units=metric&appid=%3";
    url = url.arg(lat, lon, api_key);
    network_manager->get(QNetworkRequest(QUrl(url)));
}

void LocationForecast::onRequestProcessed(QNetworkReply *reply){
    if(!reply->error()){
        qDebug() << "downloaded";
        QJsonDocument json_answer =  QJsonDocument::fromJson(reply->readAll());
         QVariantMap data_map = json_answer.toVariant().toMap();
         int offset = data_map["timezone_offset"].toInt();
         QVariantMap current_dataset = data_map["current"].toMap();
         int today = QDateTime::fromSecsSinceEpoch(current_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset).date().day();
         QVariantList hourly_dataset = data_map["hourly"].toList();
         QVariantList daily_dataset = data_map["daily"].toList();

         current_widget->update_widget_info(current_dataset, offset);
         for (auto i = 0; i < 47; i++)
             hourly_widgets[i]->update_widget_info(hourly_dataset[i + 1].toMap(), today, offset);
         for (auto i = 0; i < 7; i++)
             daily_widgets[i]->update_widget_info(daily_dataset[i + 1].toMap(), offset);
         latitude->setText(data_map["lat"].toString());
         longitude->setText(data_map["lon"].toString());

         if (previous_update_failed) {

         }
         last_update_time_val->setText(QLocale::system().toString(QDateTime::currentDateTime()));
     }
     reply->deleteLater();
     update_btn->setEnabled(true);
     update_btn->setText("Обновить");
}

QString LocationForecast::getLat(){
    return latitude->text();
}

QString LocationForecast::getLon(){
    return longitude->text();
}

void LocationForecast::setDarkThemeEnabled(bool value)
{
    if (value) {
        setStyleSheet("QWidget { color: white; background-color: rgb(1, 87, 155); border-radius: 12px}"
                      "LocationForecast { background: rgb(55, 71, 79); border-radius: 0px }"
                      "QPushButton {font: bold 14 px }"
                      "QPushButton::hover {background: rgb(1, 75,133) }");

        forecasts_frame->setStyleSheet(".QFrame {background: rgb(55, 71, 79) }"
                                       "QFrame > QLabel {background: rgb(55, 71, 79); font: bold 20px;}");

    } else {
        setStyleSheet("QWidget { color: white; background: rgb(255, 171, 64); border-radius: 12px }"
                      "LocationForecast { background: white; border-radius: 0px }"
                      "QPushButton {font: bold 14px }"
                      "QPushButton::hover {background-color: rgb(255, 152, 0) }");


        forecasts_frame->setStyleSheet(".QFrame {background: white }"
                                       "QFrame > QLabel {background: white; font: bold 20px ; color: black}");
    }
}

void LocationForecast::setLat(const QString &lat) {
    latitude->setText(lat);
}

void LocationForecast::setLon(const QString &lon) {
    longitude->setText(lon);
}


