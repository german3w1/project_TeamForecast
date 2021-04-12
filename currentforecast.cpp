#include "currentforecast.h"
#include <weathertools.h>

CurrentForecast::CurrentForecast(QWidget *parent) : QFrame(parent)
{
    grid_layout = new QGridLayout;
    setLayout(grid_layout);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setContentsMargins(4,4,4,4);
    setStyleSheet("QFrame {background: #FFAB40; border: 0px; border-radius: 16px;}");

    m_time = new QLabel;
    m_time->setStyleSheet("QLabel {font: bold 44px; color: white}");
    m_icon = new QLabel;
    m_temp = new QLabel("Температура");
    m_temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    m_temp_value = new QLabel;
    m_temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    m_feels_like = new QLabel("Ощущается");
    m_feels_like->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    m_feels_like_value = new QLabel;
    m_feels_like_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    blank_space = new QLabel;

    m_pressure = generateBoldLabel("Давление");
    m_wind = generateBoldLabel("Ветер");
    m_humidity = generateBoldLabel("Влажность");
    m_clouds = generateBoldLabel("Облачность");
    m_dew_point =generateBoldLabel("Точка росы");
    m_visibility = generateBoldLabel("Видимость");
    m_uv_ix = generateBoldLabel("УФ-индекс");
    m_pressure_value = generatePaleLabel();
    m_wind_value = generatePaleLabel();
    m_humidity_value = generatePaleLabel();
    m_clouds_value = generatePaleLabel();
    m_dew_point_value = generatePaleLabel();
    m_visibility_value = generatePaleLabel();
    m_uv_ix_value = generatePaleLabel();

    grid_layout->addWidget(m_time, 0, 0, 4, 2, Qt::Alignment(Qt::AlignVCenter));
    grid_layout->addWidget(m_icon, 0, 2, 4, 1, Qt::AlignCenter);  
    grid_layout->addWidget(m_temp, 0, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    grid_layout->addWidget(m_temp_value, 0, 5, 2, 1, Qt::Alignment(Qt::AlignRight));  
    grid_layout->addWidget(m_feels_like, 2, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    grid_layout->addWidget(m_feels_like_value, 2, 5, 2, 1, Qt::Alignment(Qt::AlignRight));   
    grid_layout->addWidget(blank_space, 4, 0, 1, 6);    
    grid_layout->addWidget(m_pressure, 5, 0, 1, 1);
    grid_layout->addWidget(m_pressure_value, 5, 1, 1, 2);   
    grid_layout->addWidget(m_wind, 5, 3, 1, 1);
    grid_layout->addWidget(m_wind_value, 5, 4, 1, 2);
    grid_layout->addWidget(m_humidity, 6, 0);
    grid_layout->addWidget(m_humidity_value, 6, 1);
    grid_layout->addWidget(m_clouds, 6, 2);
    grid_layout->addWidget(m_clouds_value, 6, 3);
    grid_layout->addWidget(m_dew_point, 6, 4);
    grid_layout->addWidget(m_dew_point_value, 6, 5);
    grid_layout->addWidget(m_visibility, 7, 0);
    grid_layout->addWidget(m_visibility_value, 7, 1);
    grid_layout->addWidget(m_uv_ix, 7, 2);
    grid_layout->addWidget(m_uv_ix_value, 7, 3);
}

QLabel* CurrentForecast::generateBoldLabel(const QString &text){
    QLabel* label = new QLabel(text);
    label->setStyleSheet("QLabel {font: bold 14px; color: white;}");
    return label;
}

QLabel* CurrentForecast::generatePaleLabel(){
    QLabel* label = new QLabel;
    label->setStyleSheet("QLabel {font: 14px; color: white;}");
    return label;
}

void CurrentForecast::update_widget_info(const QVariantMap &new_dataset, const int &offset) {
    QTime time = QDateTime::fromSecsSinceEpoch(new_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset).time();
    m_time->setText(time.toString("hh:mm"));

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

