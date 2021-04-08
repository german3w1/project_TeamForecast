#include "locationforecast.h"

LocationForecast::LocationForecast(QWidget* parent, const QString &lat, const QString &lon) : QFrame(parent)
{
    setContentsMargins(0,0,0,0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("QFrame {background:white;}");
    main_layout = new QVBoxLayout(this);

    control_panel_frame = new QFrame(this);
    control_panel_frame->setContentsMargins(2,0,2,0);
    control_panel_frame->setStyleSheet("QFrame {background: #FFAB40; border: 0px; border-radius: 12px; font: 16px;}"
                                       "QLabel {color: white;}");
    control_panel_layout = new QHBoxLayout(control_panel_frame);
    latitude = new QLabel(lat, control_panel_frame);
    control_panel_layout->addWidget(latitude,1);
    longitude = new QLabel(lon, control_panel_frame);
    control_panel_layout->addWidget(longitude,1);
    last_update_time = new QLabel("Последнее успешное обновление", this);
    last_update_time->setStyleSheet("QLabel {color: white; font: bold 16px;}");
    control_panel_layout->addWidget(last_update_time, 2);
    last_update_time_val = new QLabel(this);
    control_panel_layout->addWidget(last_update_time_val,2, Qt::Alignment(Qt::AlignCenter));
    update_btn = new QPushButton("Обновить", control_panel_frame);
    update_btn->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    update_btn->setStyleSheet("QPushButton {font: bold 14px; color: white; border: 0px; border-radius: 12px;}"
                              "QPushButton::pressed {background-color: #FF9800;}");
    connect(update_btn, &QPushButton::clicked, this, &LocationForecast::onUpdateBtnClicked);
    control_panel_layout->addWidget(update_btn,1);
    control_panel_frame->setLayout(control_panel_layout);
    control_panel_frame->setFixedHeight(control_panel_frame->height() + 20);
    main_layout->addWidget(control_panel_frame);




    forecasts_frame = new QFrame(this);
    forecasts_frame->setContentsMargins(0,0,0,0);
    forecasts_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    forecasts_layout = new QHBoxLayout(forecasts_frame);
    current_and_hourly = new MainForecast(this);
    daily = new DailyForecast(this);
    forecasts_layout->addWidget(current_and_hourly);
    forecasts_layout->addWidget(daily);
    forecasts_frame->setLayout(forecasts_layout);
    main_layout->addWidget(forecasts_frame);

    setLayout(main_layout);
    previous_update_failed = false;

    network_manager = new QNetworkAccessManager(this);
    connect(network_manager, &QNetworkAccessManager::finished, this, &LocationForecast::onRequestProcessed);
    updateWeatherInfo(lat, lon);
}

void LocationForecast::onUpdateBtnClicked(){
    updateWeatherInfo(latitude->text(), longitude->text());
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
         current_and_hourly->update_weather_info(data_map["current"].toMap(), data_map["hourly"].toList(), offset);
         daily->update_weather_info(data_map["daily"].toList(), offset);
         if (previous_update_failed) {
             control_panel_frame->setStyleSheet("QFrame {background: #FFAB40; border: 0px; border-radius: 12px; font: 16px;}"
                                                "QLabel {color: white;}");
             update_btn->setStyleSheet("QPushButton {font: bold 14px; color: white; border: 0px; border-radius: 12px;}"
                                       "QPushButton::pressed {background-color: #FF9800;}");
             previous_update_failed = false;
         }
         latitude->setText(data_map["lat"].toString());
         longitude->setText(data_map["lon"].toString());
         last_update_time_val->setText(QLocale::system().toString(QDateTime::currentDateTime()));
     }
     else if (!previous_update_failed) {
         control_panel_frame->setStyleSheet("QFrame {background: #D84315; border: 0px; border-radius: 12px; font: 16px;}"
                                            "QLabel {color: white;}");
         update_btn->setStyleSheet("QPushButton {font: bold 14px; color: white; border: 0px; border-radius: 12px;}"
                                   "QPushButton::pressed {background-color: #BF360C;}");
         previous_update_failed = true;
     }
     reply->deleteLater();
     update_btn->setEnabled(true);
     update_btn->setText("Обновить");
}
