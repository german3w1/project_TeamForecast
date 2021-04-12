#include "hourlyforecast.h"
#include <weathertools.h>

HourlyForecast::HourlyForecast(QWidget *parent) : ExpandingWeatherWidget(parent)
{
    m_day = new QLabel;
    m_day->setStyleSheet("QLabel {font: bold 20px; color: white; }");
    m_time = new QLabel;
    m_time->setStyleSheet("QLabel {font: bold 20px; color: white}");
    m_icon = new QLabel;
    m_temp = new QLabel("Температура");
    m_temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    m_temp_value = new QLabel;
    m_temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    m_feels_like = new QLabel("Ощущается");
    m_feels_like->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    m_feels_like_value = new QLabel;
    m_feels_like_value->setStyleSheet("QLabel {font: 20px; color: white;}");

    unhidden_layout->addWidget(m_day, 0, 0, 2, 2);
    unhidden_layout->addWidget(m_time, 2, 0, 2, 2);
    unhidden_layout->addWidget(m_icon, 0, 2, 4, 1, Qt::AlignCenter);
    unhidden_layout->addWidget(m_temp, 0, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(m_temp_value, 0, 5, 2, 1, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(m_feels_like, 2, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(m_feels_like_value, 2, 5, 2, 1, Qt::Alignment(Qt::AlignRight));

    m_pressure_value = generatePaleLabel();
    m_wind_value = generatePaleLabel();
    m_humidity_value = generatePaleLabel();
    m_clouds_value = generatePaleLabel();
    m_dew_point_value = generatePaleLabel();
    m_visibility_value = generatePaleLabel();
    m_uv_ix_value = generatePaleLabel();

    hidden_layout->addWidget(new QLabel, 0, 0, 1, 6);
    hidden_layout->addWidget(generateBoldLabel("Давление"), 1, 0, 1, 1);
    hidden_layout->addWidget(m_pressure_value, 1, 1, 1, 2);
    hidden_layout->addWidget(generateBoldLabel("Ветер"), 1, 3, 1, 1);
    hidden_layout->addWidget(m_wind_value, 1, 4, 1, 2);
    hidden_layout->addWidget(generateBoldLabel("Влажность"), 2, 0);
    hidden_layout->addWidget(m_humidity_value, 2, 1);
    hidden_layout->addWidget(generateBoldLabel("Облачность"), 2, 2);
    hidden_layout->addWidget(m_clouds_value, 2, 3);
    hidden_layout->addWidget(generateBoldLabel("Точка росы"), 2, 4);
    hidden_layout->addWidget(m_dew_point_value, 2, 5);
    hidden_layout->addWidget(generateBoldLabel("Видимость"), 3, 0);
    hidden_layout->addWidget(m_visibility_value, 3, 1);
    hidden_layout->addWidget(generateBoldLabel("УФ-индекс"), 3, 2);
    hidden_layout->addWidget(m_uv_ix_value, 3, 3);
}

void HourlyForecast::update_widget_info(const QVariantMap &new_dataset, const int &today, const int &offset) {
    QDateTime date_time = QDateTime::fromSecsSinceEpoch(new_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset);
    m_time->setText(date_time.time().toString("hh:mm"));
    if (int diff = date_time.date().day() - today; diff == 0)
        m_day->setText("Сегодня");
    else if (diff == 1)
        m_day->setText("Завтра");
    else
        m_day->setText("Послезавтра");

    QVariantMap weather = new_dataset["weather"].toList()[0].toMap();
    m_icon->setPixmap(WeatherTools::getWeatherIcon(weather["id"].toInt()));

    m_temp_value->setText(QString("%1°C").arg(round(new_dataset["temp"].toDouble())));
    m_feels_like_value->setText(QString("%1°C").arg(round(new_dataset["feels_like"].toDouble())));
    m_pressure_value->setText(QString("%1мм рт.ст").arg(round(new_dataset["pressure"].toDouble() / 1.333)));
    m_humidity_value->setText(new_dataset["humidity"].toString() + "%");
    m_dew_point_value->setText(QString("%1°C").arg(round(new_dataset["dew_point"].toDouble())));
    m_uv_ix_value->setText(new_dataset["uvi"].toString());
    m_clouds_value->setText(new_dataset["clouds"].toString() + "%");
    if (double visibility = new_dataset["visibility"].toDouble(); visibility > 1000)
        m_visibility_value->setText(QString("%1км").arg(visibility / 1000));
    else
        m_visibility_value->setText(QString("%1м").arg(visibility));
    auto wind_direction = WeatherTools::getWindDirection(new_dataset["wind_deg"].toInt());
    auto wind_speed = round(new_dataset["wind_speed"].toDouble());
    m_wind_value->setText(QString::number(wind_speed) + "м/с, " + wind_direction);

}


HourlyForecast::~HourlyForecast(){

}
