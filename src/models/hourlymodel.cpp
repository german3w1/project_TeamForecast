#include "models/hourlymodel.h"

HourlyModel::HourlyModel()
    : AbstractWeatherModel()
{
}

void HourlyModel::updateModel(const QVariantMap& new_data, const QDateTime& today, const int& offset)
{
    data["today"] = today;
    data["date_time"] = QDateTime::fromSecsSinceEpoch(new_data["dt"].toLongLong(), Qt::OffsetFromUTC, offset);
    data["temperature"] = new_data["temp"];
    data["reelfeel"] = new_data["feels_like"];
    data["pressure"] = new_data["pressure"];
    data["humidity"] = new_data["humidity"];
    data["dew_point"] = new_data["dew_point"];
    data["wind_speed"] = new_data["wind_speed"];
    data["wind_deg"] = new_data["wind_deg"];
    data["cloudness"] = new_data["clouds"];
    data["uvi"] = new_data["uvi"];
    data["weather_ID"] = new_data["weather"].toList()[0].toMap()["id"].toInt();
    data["visibility"] = new_data["visibility"];
}

QString HourlyModel::day() const
{
    if (auto diff = today().daysTo(data["date_time"].toDateTime()); diff == 0)
        return QObject::tr("Сегодня");
    else if (diff == 1)
        return QObject::tr("Завтра");
    else
        return QObject::tr("Послезавтра");
}
