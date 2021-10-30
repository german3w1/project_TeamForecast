#include "src/views/dailywidget.h"

DailyWidget::DailyWidget(QWidget* parent)
    : ExpandingWeatherWidget(parent)
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
    hidden_layout->addWidget(generateBoldLabel("Давление"), 1, 0, 1, 1);
    hidden_layout->addWidget(pressure_value, 1, 1, 1, 2);
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

void DailyWidget::updateWidgetInfo(const DailyModel& model)
{
    day_of_week->setText(model.dayOfWeek());
    date->setText(model.date());
    icon->setPixmap(model.weatherIcon());

    min_temp_value->setText(model.temperature("min"));
    max_temp_value->setText(model.temperature("max"));
    pressure_value->setText(model.pressure());
    humidity_value->setText(model.humidity());
    dew_point_value->setText(model.dewPoint());
    uv_ix_value->setText(model.uvi());
    clouds_value->setText(model.cloudness());
    wind_value->setText(model.wind());

    morn_temp_value->setText(model.temperature("morning"));
    day_temp_value->setText(model.temperature("day"));
    eve_temp_value->setText(model.temperature("evening"));
    night_temp_value->setText(model.temperature("night"));
    morn_fl_value->setText(model.temperature("morning_reelfeel"));
    day_fl_value->setText(model.temperature("day_reelfeel"));
    eve_fl_value->setText(model.temperature("evening_reelfeel"));
    night_fl_value->setText(model.temperature("night_reelfeel"));
}

DailyWidget::~DailyWidget()
{
}
