#include "dailywidget.h"


DailyWidget::DailyWidget(QWidget *parent) : QWidget(parent)
{
    grid_layout = new QGridLayout(this);
    setMaximumSize(450, 300);
    setContentsMargins(4,4,4,4);
    setStyleSheet("QWidget {background: #FFAB40; border: none; border-radius: 16px;}");
    auto labels_style = QString("QLabel {font: bold 14px; color: white;}");
    auto values_style = QString("QLabel {font: 14px; color: white;}");

    m_day_of_week = new QLabel(this);
    m_day_of_week->setStyleSheet("QLabel {font: bold 20px; color: white}");
    grid_layout->addWidget(m_day_of_week, 0, 0, 2, 2);

    m_date = new QLabel(this);
    m_date->setStyleSheet("QLabel {font: bold 20px; color: white; }");
    grid_layout->addWidget(m_date, 2, 0, 2, 2);

    m_min_temp = new QLabel("Минимум", this);
    m_min_temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    grid_layout->addWidget(m_min_temp, 0, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    m_min_temp_value = new QLabel(this);
    m_min_temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    grid_layout->addWidget(m_min_temp_value, 0, 5, 2, 1, Qt::Alignment(Qt::AlignRight));

    m_max_temp = new QLabel("Максимум", this);
    m_max_temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    grid_layout->addWidget(m_max_temp, 2, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    m_max_temp_value = new QLabel(this);
    m_max_temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    grid_layout->addWidget(m_max_temp_value, 2, 5, 2, 1, Qt::Alignment(Qt::AlignRight));

    m_blank_space = new QLabel(this);
    grid_layout->addWidget(m_blank_space, 4, 0, 1, 6);

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
    grid_layout->addWidget(m_pressure, 7, 0, 1, 1 );
    m_pressure_value = new QLabel(this);
    m_pressure_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_pressure_value, 7, 2, 1, 2);

    m_wind = new QLabel("Ветер", this);
    m_wind->setStyleSheet(labels_style);
    grid_layout->addWidget(m_wind, 7, 3, 1, 1, Qt::Alignment(Qt::AlignRight));
    m_wind_value = new QLabel(this);
    m_wind_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_wind_value, 7, 4, 1, 2);

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


    m_second_blank_space = new QLabel(this);
    grid_layout->addWidget(m_second_blank_space, 8, 0, 1, 6);

    m_morn_temp = new QLabel("Температура утром", this);
    m_morn_temp->setStyleSheet(labels_style);
    grid_layout->addWidget(m_morn_temp, 9, 0, 1, 2);
    m_morn_temp_value = new QLabel(this);
    m_morn_temp_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_morn_temp_value, 9, 2, 1, 1, Qt::Alignment(Qt::AlignRight));

    m_feels_like_label[0] = new QLabel("Ощущается", this);
    m_feels_like_label[0]->setStyleSheet(labels_style);
    grid_layout->addWidget(m_feels_like_label[0], 9, 3, 1, 2, Qt::Alignment(Qt::AlignRight));
    m_morn_fl_value = new QLabel(this);
    m_morn_fl_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_morn_fl_value, 9, 5, 1, 1, Qt::Alignment(Qt::AlignRight));

    m_day_temp = new QLabel("Температура днём", this);
    m_day_temp->setStyleSheet(labels_style);
    grid_layout->addWidget(m_day_temp, 10, 0, 1, 2);
    m_day_temp_value = new QLabel(this);
    m_day_temp_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_day_temp_value, 10, 2, 1, 1, Qt::Alignment(Qt::AlignRight));

    m_feels_like_label[1] = new QLabel("Ощущается", this);
    m_feels_like_label[1]->setStyleSheet(labels_style);
    grid_layout->addWidget(m_feels_like_label[1], 10, 3, 1, 2, Qt::Alignment(Qt::AlignRight));
    m_day_fl_value = new QLabel(this);
    m_day_fl_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_day_fl_value, 10, 5, 1, 1, Qt::Alignment(Qt::AlignRight));

    m_eve_temp = new QLabel("Температура вечером", this);
    m_eve_temp->setStyleSheet(labels_style);
    grid_layout->addWidget(m_eve_temp, 11, 0, 1, 2);
    m_eve_temp_value = new QLabel(this);
    m_eve_temp_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_eve_temp_value, 11, 2, 1, 1, Qt::Alignment(Qt::AlignRight));

    m_feels_like_label[2] = new QLabel("Ощущается", this);
    m_feels_like_label[2]->setStyleSheet(labels_style);
    grid_layout->addWidget(m_feels_like_label[2], 11, 3, 1, 2, Qt::Alignment(Qt::AlignRight));
    m_eve_fl_value = new QLabel(this);
    m_eve_fl_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_eve_fl_value, 11, 5, 1, 1, Qt::Alignment(Qt::AlignRight));

    m_night_temp = new QLabel("Температура ночью", this);
    m_night_temp->setStyleSheet(labels_style);
    grid_layout->addWidget(m_night_temp, 12, 0, 1, 2);
    m_night_temp_value = new QLabel(this);
    m_night_temp_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_night_temp_value, 12, 2, 1, 1, Qt::Alignment(Qt::AlignRight));

    m_feels_like_label[3] = new QLabel("Ощущается", this);
    m_feels_like_label[3]->setStyleSheet(labels_style);
    grid_layout->addWidget(m_feels_like_label[3], 12, 3, 1, 2, Qt::Alignment(Qt::AlignRight));
    m_night_fl_value = new QLabel(this);
    m_night_fl_value->setStyleSheet(values_style);
    grid_layout->addWidget(m_night_fl_value, 12, 5, 1, 1, Qt::Alignment(Qt::AlignRight));

    minimize();
    expanded = false;
}

void DailyWidget::update_widget_info(const QVariantMap &new_dataset, const int &offset) {
   QVariantMap new_dataset_temp = new_dataset["temp"].toMap();
   QVariantMap new_dataset_fl = new_dataset["feels_like"].toMap();
   QDate date = QDateTime::fromSecsSinceEpoch(new_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset).date();
   QLocale locale = QLocale::system();
   m_day_of_week->setText(locale.dayName(date.dayOfWeek()));
   m_date->setText(date.toString("dd.MM"));

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
   auto wind_direction = getWindDirection(new_dataset["wind_deg"].toInt());
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

QString DailyWidget::getWindDirection(const int &degrees){
    if (degrees == 0) return "С";
    else if (0 < degrees && degrees < 90) return "СВ";
    else if (degrees == 90) return "В";
    else if (90 < degrees && degrees < 180) return "ЮВ";
    else if (degrees == 180) return "Ю";
    else if (180 < degrees && degrees < 270) return "ЮЗ";
    else if (degrees == 270) return "З";
    else return "СЗ";
}

void DailyWidget::maximize(){

    m_blank_space->show();
    m_humidity->show();
    m_humidity_value->show();
    m_clouds->show();
    m_clouds_value->show();
    m_pressure->show();
    m_pressure_value->show();
    m_uv_ix->show();
    m_uv_ix_value->show();
    m_visibility->show();
    m_visibility_value->show();
    m_dew_point->show();
    m_dew_point_value->show();
    m_wind->show();
    m_wind_value->show();

    m_second_blank_space->show();
    m_morn_temp->show();
    m_morn_temp_value->show();
    m_day_temp->show();
    m_day_temp_value->show();
    m_eve_temp->show();
    m_eve_temp_value->show();
    m_night_temp->show();
    m_night_temp_value->show();
    for (auto i = 0; i < 4; i++)
        m_feels_like_label[i]->show();
    m_morn_fl_value->show();
    m_day_fl_value->show();
    m_eve_fl_value->show();
    m_night_fl_value->show();

    expanded = true;
}

void DailyWidget::minimize(){

    m_blank_space->hide();
    m_humidity->hide();
    m_humidity_value->hide();
    m_clouds->hide();
    m_clouds_value->hide();
    m_pressure->hide();
    m_pressure_value->hide();
    m_uv_ix->hide();
    m_uv_ix_value->hide();
    m_visibility->hide();
    m_visibility_value->hide();
    m_dew_point->hide();
    m_dew_point_value->hide();
    m_wind->hide();
    m_wind_value->hide();

    m_second_blank_space->hide();
    m_morn_temp->hide();
    m_morn_temp_value->hide();
    m_day_temp->hide();
    m_day_temp_value->hide();
    m_eve_temp->hide();
    m_eve_temp_value->hide();
    m_night_temp->hide();
    m_night_temp_value->hide();
    for (auto i = 0; i < 4; i++)
        m_feels_like_label[i]->hide();
    m_morn_fl_value->hide();
    m_day_fl_value->hide();
    m_eve_fl_value->hide();
    m_night_fl_value->hide();

    expanded = false;
}

void DailyWidget::mousePressEvent(QMouseEvent *event){
    if (!expanded){
        maximize();
        emit pressed(this);
    }
    else minimize();
}


//код, который я понятия не имею как работает, но указан в качестве
//обязательного в документации Qt при использовании stylesheets
void DailyWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

DailyWidget::~DailyWidget(){

}
