#include "src/views/currentwidget.h"

CurrentWidget::CurrentWidget(QWidget* parent)
    : ExpandingWeatherWidget(parent)
{
    time = new QLabel("00:00");
    time->setStyleSheet("QLabel {font: bold 44px; color: white}");
    icon = new QLabel;
    temp = new QLabel("Температура");
    temp->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    temp_value = new QLabel;
    temp_value->setStyleSheet("QLabel {font: 20px; color: white;}");
    feels_like = new QLabel("Ощущается");
    feels_like->setStyleSheet("QLabel {font: bold 20px; color: white;}");
    feels_like_value = new QLabel;
    feels_like_value->setStyleSheet("QLabel {font: 20px; color: white;}");

    pressure_value = generatePaleLabel();
    wind_value = generatePaleLabel();
    humidity_value = generatePaleLabel();
    clouds_value = generatePaleLabel();
    dew_point_value = generatePaleLabel();
    visibility_value = generatePaleLabel();
    uv_ix_value = generatePaleLabel();

    unhidden_layout->addWidget(time, 0, 0, 4, 2, Qt::Alignment(Qt::AlignVCenter));
    unhidden_layout->addWidget(icon, 0, 2, 4, 1, Qt::AlignCenter);
    unhidden_layout->addWidget(temp, 0, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(temp_value, 0, 5, 2, 1, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(feels_like, 2, 3, 2, 2, Qt::Alignment(Qt::AlignRight));
    unhidden_layout->addWidget(feels_like_value, 2, 5, 2, 1, Qt::Alignment(Qt::AlignRight));

    hidden_layout->addWidget(new QLabel, 0, 0, 1, 6);
    hidden_layout->addWidget(generateBoldLabel("Давление"), 1, 0, 1, 1);
    hidden_layout->addWidget(pressure_value, 1, 1, 1, 2);
    hidden_layout->addWidget(generateBoldLabel("Ветер"), 1, 3, 1, 1);
    hidden_layout->addWidget(wind_value, 1, 4, 1, 2);
    hidden_layout->addWidget(generateBoldLabel("Влажность"), 2, 0);
    hidden_layout->addWidget(humidity_value, 2, 1);
    hidden_layout->addWidget(generateBoldLabel("Облачность"), 2, 2);
    hidden_layout->addWidget(clouds_value, 2, 3);
    hidden_layout->addWidget(generateBoldLabel("Точка росы"), 2, 4);
    hidden_layout->addWidget(dew_point_value, 2, 5);
    hidden_layout->addWidget(generateBoldLabel("Видимость"), 3, 0);
    hidden_layout->addWidget(visibility_value, 3, 1);
    hidden_layout->addWidget(generateBoldLabel("УФ-индекс"), 3, 2);
    hidden_layout->addWidget(uv_ix_value, 3, 3);
}

void CurrentWidget::updateWidgetInfo(const CurrentModel& model)
{
    time->setText(model.time());
    icon->setPixmap(model.weatherIcon());

    temp_value->setText(model.temperature("temperature"));
    feels_like_value->setText(model.temperature("reelfeel"));
    pressure_value->setText(model.pressure());
    humidity_value->setText(model.humidity());
    dew_point_value->setText(model.dewPoint());
    uv_ix_value->setText(model.uvi());
    clouds_value->setText(model.cloudness());
    visibility_value->setText(model.visibility());
    wind_value->setText(model.wind());
}

CurrentWidget::~CurrentWidget()
{
}
