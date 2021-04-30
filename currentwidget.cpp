#include "currentwidget.h"

CurrentWidget::CurrentWidget(QWidget *parent) : ExpandingWeatherWidget(parent)
{
    time = new QLabel;
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

void CurrentWidget::updateWidgetInfo(const QVariantMap &new_dataset, const int &offset)
{
    QTime time_value = QDateTime::fromSecsSinceEpoch(new_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset).time();
    time->setText(time_value.toString("hh:mm"));

    QVariantMap weather = new_dataset["weather"].toList()[0].toMap();
    icon->setPixmap(getWeatherIcon(weather["id"].toInt()));

    temp_value->setText(QString("%1°C").arg(round(new_dataset["temp"].toDouble())));
    feels_like_value->setText(QString("%1°C").arg(round(new_dataset["feels_like"].toDouble())));
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
}

CurrentWidget::~CurrentWidget()
{

}
