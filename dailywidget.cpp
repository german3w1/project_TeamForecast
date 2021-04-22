#include "dailywidget.h"
#include <weathertools.h>

DailyWidget::DailyWidget(QWidget *parent) : ExpandingWeatherWidget(parent)
{

    m_day_of_week = new QLabel;
    m_day_of_week->setStyleSheet("QLabel {font: bold 20px; color: white}");
    m_date = new QLabel;
    m_date->setStyleSheet("QLabel {font: bold 20px; color: white; }");
    m_icon = new QLabel;
    m_min_temp = new QLabel("Минимум");
    m_min_temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    m_min_temp_value = new QLabel;
    m_min_temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    m_max_temp = new QLabel("Максимум");
    m_max_temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    m_max_temp_value = new QLabel;
    m_max_temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");

    unhidden_layout->addWidget(m_day_of_week, 0, 0, 2, 1);
    unhidden_layout->addWidget(m_date, 2, 0, 2, 1);
    unhidden_layout->addWidget(m_icon, 0, 1, 4, 2, Qt::AlignRight);
    unhidden_layout->addWidget(m_min_temp, 0, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(m_min_temp_value, 0, 5, 2, 1, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(m_max_temp, 2, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(m_max_temp_value, 2, 5, 2, 1, Qt::Alignment(Qt::AlignRight));

    m_humidity_value = generatePaleLabel();
    m_clouds_value = generatePaleLabel();
    m_pressure_value = generatePaleLabel();
    m_wind_value = generatePaleLabel();
    m_uv_ix_value = generatePaleLabel();
    m_visibility_value = generatePaleLabel();
    m_dew_point_value = generatePaleLabel();
    m_morn_temp_value = generatePaleLabel();
    m_morn_fl_value = generatePaleLabel();
    m_day_temp_value = generatePaleLabel();
    m_day_fl_value = generatePaleLabel();
    m_eve_temp_value = generatePaleLabel();
    m_eve_fl_value = generatePaleLabel();
    m_night_temp_value = generatePaleLabel();
    m_night_fl_value = generatePaleLabel();

    hidden_layout->addWidget(new QLabel, 0, 0, 1, 6);
    hidden_layout->addWidget(generateBoldLabel("Давление"), 1, 0, 1, 1 );
    hidden_layout->addWidget(m_pressure_value, 1, 2, 1, 2);
    hidden_layout->addWidget(generateBoldLabel("Ветер"), 1, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(m_wind_value, 1, 4, 1, 2);
    hidden_layout->addWidget(generateBoldLabel("Влажность"), 3, 0);
    hidden_layout->addWidget(m_humidity_value, 3, 1);
    hidden_layout->addWidget(generateBoldLabel("Облачность"), 3, 2);
    hidden_layout->addWidget(m_clouds_value, 3, 3);
    hidden_layout->addWidget(generateBoldLabel("УФ-индекс"), 2, 2);
    hidden_layout->addWidget(m_uv_ix_value, 2, 3);
    hidden_layout->addWidget(generateBoldLabel("Видимость"), 2, 0);
    hidden_layout->addWidget(m_visibility_value, 2, 1);
    hidden_layout->addWidget(generateBoldLabel("Точка росы"), 2, 4);
    hidden_layout->addWidget(m_dew_point_value, 2, 5);
    hidden_layout->addWidget(new QLabel, 4, 0, 1, 6);
    hidden_layout->addWidget(generateBoldLabel("Утром"), 5, 0, 1, 1);
    hidden_layout->addWidget(m_morn_temp_value, 5, 1, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ощущается"), 5, 2, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(m_morn_fl_value, 5, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Днём"), 6, 0, 1, 1);
    hidden_layout->addWidget(m_day_temp_value, 6, 1, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ощущается"), 6, 2, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(m_day_fl_value, 6, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Вечером"), 7, 0, 1, 1);
    hidden_layout->addWidget(m_eve_temp_value, 7, 1, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ощущается"), 7, 2, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(m_eve_fl_value, 7, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ночью"), 8, 0, 1, 1);
    hidden_layout->addWidget(m_night_temp_value, 8, 1, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ощущается"), 8, 2, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(m_night_fl_value, 8, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
}

void DailyWidget::update_widget_info(const QVariantMap &new_dataset, const int &offset)
{
   QVariantMap new_dataset_temp = new_dataset["temp"].toMap();
   QVariantMap new_dataset_fl = new_dataset["feels_like"].toMap();
   QDate date = QDateTime::fromSecsSinceEpoch(new_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset).date();
   QLocale locale = QLocale::system();
   m_day_of_week->setText(locale.dayName(date.dayOfWeek(), QLocale::ShortFormat));
   m_date->setText(date.toString("dd.MM"));

   QVariantMap weather = new_dataset["weather"].toList()[0].toMap();
   m_icon->setPixmap(WeatherTools::getWeatherIcon(weather["id"].toInt()));

   m_min_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["min"].toDouble())));
   m_max_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["max"].toDouble())));
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

   m_morn_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["morn"].toDouble())));
   m_day_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["day"].toDouble())));
   m_eve_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["eve"].toDouble())));
   m_night_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["night"].toDouble())));
   m_morn_fl_value->setText(QString("%1°C").arg(round(new_dataset_fl["morn"].toDouble())));
   m_day_fl_value->setText(QString("%1°C").arg(round(new_dataset_fl["day"].toDouble())));
   m_eve_fl_value->setText(QString("%1°C").arg(round(new_dataset_fl["eve"].toDouble())));
   m_night_fl_value->setText(QString("%1°C").arg(round(new_dataset_fl["night"].toDouble())));


}

DailyWidget::~DailyWidget()
{
}
