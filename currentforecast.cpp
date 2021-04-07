#include "currentforecast.h"

CurrentForecast::CurrentForecast(QWidget *parent) : QFrame(parent)
{
    grid_layout = new QGridLayout(this);
    setFixedSize(465, 180);
    setContentsMargins(4,4,4,4);
    setStyleSheet("QFrame {background: #FFAB40; border: 0px; border-radius: 16px;}");
    auto labels_style = QString("QLabel {font: bold 14px; color: white;}");
    auto values_style = QString("QLabel {font: 14px; color: white;}");

    m_time = new QLabel(this);
    m_time->setStyleSheet("QLabel {font: bold 44px; color: white}");
    grid_layout->addWidget(m_time, 0, 0, 4, 2, Qt::Alignment(Qt::AlignVCenter));

    m_temp = new QLabel("Температура", this);
    m_temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    grid_layout->addWidget(m_temp, 0, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    m_temp_value = new QLabel(this);
    m_temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    grid_layout->addWidget(m_temp_value, 0, 5, 2, 1, Qt::Alignment(Qt::AlignRight));

    m_feels_like = new QLabel("Ощущается", this);
    m_feels_like->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    grid_layout->addWidget(m_feels_like, 2, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    m_feels_like_value = new QLabel(this);
    m_feels_like_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    grid_layout->addWidget(m_feels_like_value, 2, 5, 2, 1, Qt::Alignment(Qt::AlignRight));

    blank_space = new QLabel(this);
    //blank_space->setPixmap(QPixmap(":/icons/white_line.PNG").scaled(430, 1));
    grid_layout->addWidget(blank_space, 4, 0, 1, 6);

    m_humidity = new QLabel("Влажность", this);
    m_humidity->setStyleSheet(labels_style);
    grid_layout->addWidget(m_humidity, 5, 0);
    m_humidity_value = new QLabel(this);
    m_humidity_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_humidity_value, 5, 1);

    m_clouds = new QLabel("Облачность", this);
    m_clouds->setStyleSheet(labels_style);
    grid_layout->addWidget(m_clouds, 5, 2);
    m_clouds_value = new QLabel(this);
    m_clouds_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_clouds_value, 5, 3);

    m_pressure = new QLabel("Давление", this);
    m_pressure->setStyleSheet(labels_style);
    grid_layout->addWidget(m_pressure, 5, 4, Qt::Alignment(Qt::AlignRight));
    m_pressure_value = new QLabel(this);
    m_pressure_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_pressure_value, 5, 5);

    m_uv_ix = new QLabel("УФ-индекс", this);
    m_uv_ix->setStyleSheet(labels_style);
    grid_layout->addWidget(m_uv_ix, 6, 2);
    m_uv_ix_value = new QLabel(this);
    m_uv_ix_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_uv_ix_value, 6, 3);

    m_visibility = new QLabel("Видимость", this);
    m_visibility->setStyleSheet(labels_style);
    grid_layout->addWidget(m_visibility, 6, 0);
    m_visibility_value = new QLabel(this);
    m_visibility_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_visibility_value, 6, 1);

    m_dew_point = new QLabel("Точка росы", this);
    m_dew_point->setStyleSheet(labels_style);
    grid_layout->addWidget(m_dew_point, 6, 4);
    m_dew_point_value = new QLabel(this);
    m_dew_point_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_dew_point_value, 6, 5);

    m_wind_deg = new QLabel("Направление ветра", this);
    m_wind_deg->setStyleSheet(labels_style);
    grid_layout->addWidget(m_wind_deg, 7, 0, 1, 2);
    m_wind_deg_value = new QLabel(this);
    m_wind_deg_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_wind_deg_value, 7, 2, 1, 1);

    m_wind_speed = new QLabel("Скорость ветра", this);
    m_wind_speed->setStyleSheet(labels_style);
    grid_layout->addWidget(m_wind_speed, 7, 3, 1, 2, Qt::Alignment(Qt::AlignRight));
    m_wind_speed_value = new QLabel(this);
    m_wind_speed_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_wind_speed_value, 7, 5, 1, 1);

    setLayout(grid_layout);
}

void CurrentForecast::update_widget_info(const QVariantMap &new_dataset, const int &offset) {
    QTime time = QDateTime::fromSecsSinceEpoch(new_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset).time();
    m_time->setText(time.toString("hh:mm"));
    m_temp_value->setText(QString("%1°C").arg(round(new_dataset["temp"].toDouble())));
    m_feels_like_value->setText(QString("%1°C").arg(round(new_dataset["feels_like"].toDouble())));
    m_pressure_value->setText(QString("%1мм рт.ст").arg(round(new_dataset["pressure"].toDouble() / 1.333)));
    m_humidity_value->setText(new_dataset["humidity"].toString() + "%");
    m_dew_point_value->setText(QString("%1°C").arg(round(new_dataset["dew_point"].toDouble())));
    m_uv_ix_value->setText(new_dataset["uvi"].toString());
    m_clouds_value->setText(new_dataset["clouds"].toString() + "%");
    m_visibility_value->setText(QString("%1км").arg(new_dataset["visibility"].toDouble() / 1000));
    m_wind_speed_value->setText(new_dataset["wind_speed"].toString() + "м/с");
    m_wind_deg_value->setText(getWindDirection(new_dataset["wind_deg"].toInt()));
}

QString CurrentForecast::getWindDirection(const int &degrees){
    if (degrees == 0) return "С";
    else if (0 < degrees && degrees < 90) return "СВ";
    else if (degrees == 90) return "В";
    else if (90 < degrees && degrees < 180) return "ЮВ";
    else if (degrees == 180) return "Ю";
    else if (180 < degrees && degrees < 270) return "ЮЗ";
    else if (degrees == 270) return "З";
    else return "СЗ";
}
