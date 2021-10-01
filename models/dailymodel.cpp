#include "models/dailymodel.h"

DailyModel::DailyModel() : AbstractWeatherModel()
{

}

 void DailyModel::updateModel(const QVariantMap &new_data, const int &offset)
{
    data["date"] = QDateTime::fromSecsSinceEpoch(new_data["dt"].toLongLong(), Qt::OffsetFromUTC, offset).date();

    auto temp = new_data["temp"].toMap();
    data["min"] = temp["min"];
    data["max"] = temp["max"];
    data["morning"] = temp["morn"];
    data["day"] = temp["day"];
    data["evening"] = temp["eve"];
    data["night"] = temp["night"];

    auto reelfeel = new_data["feels_like"].toMap();
    data["morning_reelfeel"] = reelfeel["morn"];
    data["day_reelfeel"] = reelfeel["day"];
    data["evening_reelfeel"] = reelfeel["eve"];
    data["night_reelfeel"] = reelfeel["night"];

    data["pressure"] = new_data["pressure"];
    data["humidity"] = new_data["humidity"];
    data["dew_point"] = new_data["dew_point"];
    data["wind_speed"] = new_data["wind_speed"];
    data["wind_deg"] = new_data["wind_deg"];
    data["cloudness"] = new_data["clouds"];
    data["uvi"] = new_data["uvi"];
    data["weather_ID"] = new_data["weather"].toList()[0].toMap()["id"].toInt();
}
