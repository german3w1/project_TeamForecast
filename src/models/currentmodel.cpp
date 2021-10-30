#include "src/models/currentmodel.h"

CurrentModel::CurrentModel()
    : AbstractWeatherModel()
{
}

void CurrentModel::updateModel(QVariantMap& new_data, const int& offset)
{
    data["time"] = QDateTime::fromSecsSinceEpoch(new_data["dt"].toLongLong(), Qt::OffsetFromUTC, offset).time();
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
