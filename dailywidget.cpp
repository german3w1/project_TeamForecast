#include "dailywidget.h"

DailyWidget::DailyWidget(QWidget *parent) : ExpandingWeatherWidget(parent)
{

    day_of_week = new QLabel;
    day_of_week->setStyleSheet("QLabel {font: bold 20px; color: white}");
    date = new QLabel;
    date->setStyleSheet("QLabel {font: bold 20px; color: white; }");
    icon = new QLabel;
    min_temp = new QLabel("Минимум");
    min_temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    min_temp_value = new QLabel;
    min_temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    max_temp = new QLabel("Максимум");
    max_temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    max_temp_value = new QLabel;
    max_temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");

    unhidden_layout->addWidget(day_of_week, 0, 0, 2, 1);
    unhidden_layout->addWidget(date, 2, 0, 2, 1);
    unhidden_layout->addWidget(icon, 0, 1, 4, 2, Qt::AlignRight);
    unhidden_layout->addWidget(min_temp, 0, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(min_temp_value, 0, 5, 2, 1, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(max_temp, 2, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(max_temp_value, 2, 5, 2, 1, Qt::Alignment(Qt::AlignRight));

    humidity_value = generatePaleLabel();
    clouds_value = generatePaleLabel();
    pressure_value = generatePaleLabel();
    wind_value = generatePaleLabel();
    uv_ix_value = generatePaleLabel();
    visibility_value = generatePaleLabel();
    dew_point_value = generatePaleLabel();
    morn_temp_value = generatePaleLabel();
    morn_fl_value = generatePaleLabel();
    day_temp_value = generatePaleLabel();
    day_fl_value = generatePaleLabel();
    eve_temp_value = generatePaleLabel();
    eve_fl_value = generatePaleLabel();
    night_temp_value = generatePaleLabel();
    night_fl_value = generatePaleLabel();

    hidden_layout->addWidget(new QLabel, 0, 0, 1, 6);
    hidden_layout->addWidget(generateBoldLabel("Давление"), 1, 0, 1, 1 );
    hidden_layout->addWidget(pressure_value, 1, 2, 1, 2);
    hidden_layout->addWidget(generateBoldLabel("Ветер"), 1, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(wind_value, 1, 4, 1, 2);
    hidden_layout->addWidget(generateBoldLabel("Влажность"), 3, 0);
    hidden_layout->addWidget(humidity_value, 3, 1);
    hidden_layout->addWidget(generateBoldLabel("Облачность"), 3, 2);
    hidden_layout->addWidget(clouds_value, 3, 3);
    hidden_layout->addWidget(generateBoldLabel("УФ-индекс"), 2, 2);
    hidden_layout->addWidget(uv_ix_value, 2, 3);
    hidden_layout->addWidget(generateBoldLabel("Видимость"), 2, 0);
    hidden_layout->addWidget(visibility_value, 2, 1);
    hidden_layout->addWidget(generateBoldLabel("Точка росы"), 2, 4);
    hidden_layout->addWidget(dew_point_value, 2, 5);
    hidden_layout->addWidget(new QLabel, 4, 0, 1, 6);
    hidden_layout->addWidget(generateBoldLabel("Утром"), 5, 0, 1, 1);
    hidden_layout->addWidget(morn_temp_value, 5, 1, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ощущается"), 5, 2, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(morn_fl_value, 5, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Днём"), 6, 0, 1, 1);
    hidden_layout->addWidget(day_temp_value, 6, 1, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ощущается"), 6, 2, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(day_fl_value, 6, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Вечером"), 7, 0, 1, 1);
    hidden_layout->addWidget(eve_temp_value, 7, 1, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ощущается"), 7, 2, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(eve_fl_value, 7, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ночью"), 8, 0, 1, 1);
    hidden_layout->addWidget(night_temp_value, 8, 1, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(generateBoldLabel("Ощущается"), 8, 2, 1, 1, Qt::Alignment(Qt::AlignRight));
    hidden_layout->addWidget(night_fl_value, 8, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
}

void DailyWidget::updateWidgetInfo(const QVariantMap &new_dataset, const int &offset)
{
   QVariantMap new_dataset_temp = new_dataset["temp"].toMap();
   QVariantMap new_dataset_fl = new_dataset["feels_like"].toMap();
   QDate date_value = QDateTime::fromSecsSinceEpoch(new_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset).date();
   QLocale locale = QLocale::system();
   day_of_week->setText(locale.dayName(date_value.dayOfWeek(), QLocale::ShortFormat));
   date->setText(date_value.toString("dd.MM"));

   QVariantMap weather = new_dataset["weather"].toList()[0].toMap();
   icon->setPixmap(getWeatherIcon(weather["id"].toInt()));

   min_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["min"].toDouble())));
   max_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["max"].toDouble())));
   pressure_value->setText(QString("%1мм рт.ст").arg(round(new_dataset["pressure"].toDouble() / 1.333)));
   humidity_value->setText(new_dataset["humidity"].toString() + "%");
   dew_point_value->setText(QString("%1°C").arg(round(new_dataset["dew_point"].toDouble())));
   uv_ix_value->setText(new_dataset["uvi"].toString());
   clouds_value->setText(new_dataset["clouds"].toString() + "%");
   if (double visibility = new_dataset["visibility"].toDouble(); visibility > 1000)
       visibility_value->setText(QString("%1км").arg(visibility / 1000));
   else
       visibility_value->setText(QString("%1м").arg(visibility));
   auto wind_direction = getWindDirection(new_dataset["wind_deg"].toInt());
   auto wind_speed = round(new_dataset["wind_speed"].toDouble());
   wind_value->setText(QString::number(wind_speed) + "м/с, " + wind_direction);

   morn_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["morn"].toDouble())));
   day_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["day"].toDouble())));
   eve_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["eve"].toDouble())));
   night_temp_value->setText(QString("%1°C").arg(round(new_dataset_temp["night"].toDouble())));
   morn_fl_value->setText(QString("%1°C").arg(round(new_dataset_fl["morn"].toDouble())));
   day_fl_value->setText(QString("%1°C").arg(round(new_dataset_fl["day"].toDouble())));
   eve_fl_value->setText(QString("%1°C").arg(round(new_dataset_fl["eve"].toDouble())));
   night_fl_value->setText(QString("%1°C").arg(round(new_dataset_fl["night"].toDouble())));


}

DailyWidget::~DailyWidget()
{
}
