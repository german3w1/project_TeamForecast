#include "currentforecast.h"

CurrentForecast::CurrentForecast(QWidget *parent) : QFrame(parent)
{
    grid_layout = new QGridLayout(this);
    setFixedSize(440, 180);
    setContentsMargins(4,4,4,4);
    setStyleSheet("QFrame {background: #FFAB40; border: 0px; border-radius: 16px;}");
    auto labels_style = QString("QLabel {font: bold 14px; color: white;}");
    auto values_style = QString("QLabel {font: 14px; color: white;}");

    m_time = new QLabel(this);
    m_time->setStyleSheet("QLabel {font: bold 44px; color: white}");
    grid_layout->addWidget(m_time, 0, 0, 4, 2, Qt::Alignment(Qt::AlignVCenter));

    m_icon = new QLabel(this);
    grid_layout->addWidget(m_icon, 0, 2, 4, 1, Qt::AlignCenter);

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

    m_pressure = new QLabel("Давление", this);
    m_pressure->setStyleSheet(labels_style);
    grid_layout->addWidget(m_pressure, 5, 0, 1, 1);
    m_pressure_value = new QLabel(this);
    m_pressure_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_pressure_value, 5, 1, 1, 2);

    m_wind = new QLabel("Ветер", this);
    m_wind->setStyleSheet(labels_style);
    grid_layout->addWidget(m_wind, 5, 3, 1, 1);
    m_wind_value = new QLabel(this);
    m_wind_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_wind_value, 5, 4, 1, 2);

    m_humidity = new QLabel("Влажность", this);
    m_humidity->setStyleSheet(labels_style);
    grid_layout->addWidget(m_humidity, 6, 0);
    m_humidity_value = new QLabel(this);
    m_humidity_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_humidity_value, 6, 1);

    m_clouds = new QLabel("Облачность", this);
    m_clouds->setStyleSheet(labels_style);
    grid_layout->addWidget(m_clouds, 6, 2);
    m_clouds_value = new QLabel(this);
    m_clouds_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_clouds_value, 6, 3);

    m_dew_point = new QLabel("Точка росы", this);
    m_dew_point->setStyleSheet(labels_style);
    grid_layout->addWidget(m_dew_point, 6, 4);
    m_dew_point_value = new QLabel(this);
    m_dew_point_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_dew_point_value, 6, 5);

    m_visibility = new QLabel("Видимость", this);
    m_visibility->setStyleSheet(labels_style);
    grid_layout->addWidget(m_visibility, 7, 0);
    m_visibility_value = new QLabel(this);
    m_visibility_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_visibility_value, 7, 1);

    m_uv_ix = new QLabel("УФ-индекс", this);
    m_uv_ix->setStyleSheet(labels_style);
    grid_layout->addWidget(m_uv_ix, 7, 2);
    m_uv_ix_value = new QLabel(this);
    m_uv_ix_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_uv_ix_value, 7, 3);

    setLayout(grid_layout);
}

void CurrentForecast::update_widget_info(const QVariantMap &new_dataset, const int &offset) {
    QTime time = QDateTime::fromSecsSinceEpoch(new_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset).time();
    m_time->setText(time.toString("hh:mm"));

    //заглушка
    m_icon->setPixmap(QIcon(":/weather_states/thunderstorm").pixmap(QSize(64, 64)));

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
    auto wind_direction = getWindDirection(new_dataset["wind_deg"].toInt());
    auto wind_speed = round(new_dataset["wind_speed"].toDouble());
    m_wind_value->setText(QString::number(wind_speed) + "м/с, " + wind_direction);
}

QString CurrentForecast::getWindDirection(const int &degrees){
    if (degrees == 0) return "Северный";
    else if (0 < degrees && degrees < 90) return "Северо-Восточный";
    else if (degrees == 90) return "Восточный";
    else if (90 < degrees && degrees < 180) return "Юго-Восточный";
    else if (degrees == 180) return "Южный";
    else if (180 < degrees && degrees < 270) return "Юго-Западный";
    else if (degrees == 270) return "Западный";
    else return "Северо-Западный";
}
