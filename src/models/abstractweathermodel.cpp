#include "src/models/abstractweathermodel.h"

ushort AbstractWeatherModel::CONFIGURATION = 0x1121; ///< default configuration

PointersMap AbstractWeatherModel::pressure_functions = {
    { PRESSURE::HPA, [](double value) { return QObject::tr("%1hPa").arg(value); } },
    { PRESSURE::PA, [](double value) { return QObject::tr("%1Pa").arg(value * 100); } },
    { PRESSURE::MMHG, [](double value) { return QObject::tr("%1mmHg").arg(value / 1.333); } },
    { PRESSURE::MBAR, [](double value) { return QObject::tr("%1mbar").arg(value); } }
};

PointersMap AbstractWeatherModel::temperature_functions = {
    { TEMPERATURE::KELVIN, [](double value) { return QString("%1K").arg(round(value + 273.15)); } },
    { TEMPERATURE::FARENHEIT, [](double value) { return QString("%1°F").arg(round(value * 1.8 + 32)); } },
    { TEMPERATURE::CELSIUS, [](double value) { return QString("%1°C").arg(round(value)); } },
};

PointersMap AbstractWeatherModel::distances_functions = {
    { DISTANCE::KM, [](double value) { return QObject::tr("%1km").arg(value / 1000); } },
    { DISTANCE::MILES, [](double value) { return QObject::tr("%1miles").arg(value / 1609); } },
    { DISTANCE::METERS, [](double value) { return QObject::tr("%1m").arg(value); } },
};

PointersMap AbstractWeatherModel::windspeed_functions = {
    { WINDSPEED::METERSPERSEC, [](double value) { return QObject::tr("%1mps").arg(value); } },
    { WINDSPEED::KMPERHOUR, [](double value) { return QObject::tr("%1kph").arg(value * 3.6); } },
    { WINDSPEED::KNOT, [](double value) { return QObject::tr("%1kn").arg(value * 1.944); } },
    { WINDSPEED::FTPERSEC, [](double value) { return QObject::tr("%1fps").arg(value * 3.281); } },
    { WINDSPEED::MILESPERHOUR, [](double value) { return QObject::tr("%1mph").arg(value * 2.237); } },
};

AbstractWeatherModel::AbstractWeatherModel()
{
}

QPixmap AbstractWeatherModel::weatherIcon() const
{
    QSize icon_size(48, 48);
    int weather_id(data["weather_ID"].toInt());

    //перед просмотром этой группы switch смотри https://openweathermap.org/weather-conditions
    switch (weather_id / 100) { //чтобы сразу определить группу, к которой относятся погодные условия
    case 2: //2xx (Thunderstorm)
        return QIcon(":/weather_states/thunderstorm").pixmap(icon_size);
    case 3: //3xx (Drizzle)
        return QIcon(":/weather_states/shower_rain").pixmap(icon_size);
    case 5: //5xx (Rain)
        switch (weather_id) { //чтобы выбрать элемент внутри группы
        case 500: //fallthrough намеренно, чтобы покрыть случаи 500-504
        case 501:
        case 502:
        case 503:
        case 504:
            return QIcon(":/weather_states/rain").pixmap(icon_size);
        case 511: //freezing_rain
            return QIcon(":/weather_states/snow").pixmap(icon_size);
        case 520: //fallthrough намеренно, чтобы покрыть случаи 520, 521, 522 & 531
        case 521:
        case 522:
        case 531:
            return QIcon(":/weather_states/shower_rain").pixmap(icon_size);
        }
        break; //чтобы не fallthrough
    case 6: //6хх (Snow)
        return QIcon(":/weather_states/snow").pixmap(icon_size);
    case 7: //7хх (Atmosphere)
        return QIcon(":/weather_states/mist").pixmap(icon_size);
    case 8: //8хх (Clear & Clouds)
        switch (weather_id) {
        case 800: //clear_sky
            return QIcon(":/weather_states/clear_sky").pixmap(icon_size);
        case 801: //few_clouds
            return QIcon(":/weather_states/few_clouds").pixmap(icon_size);
        case 802: //scattered_clouds
            return QIcon(":/weather_states/scattered_clouds").pixmap(icon_size);
        case 803: //broken_clouds
            return QIcon(":/weather_states/broken_clouds").pixmap(icon_size);
        case 804: //overcast_clouds
            return QIcon(":/weather_states/overcast_clouds").pixmap(icon_size);
        }
    }
    return QIcon().pixmap(icon_size);
}

QString AbstractWeatherModel::wind() const
{
    auto wind_direction = windDirection(data["wind_deg"].toInt());
    auto wind_speed = windspeed_functions[WINDSPEED::MASK & CONFIGURATION](data["wind_speed"].toDouble());
    return wind_speed + ", " + wind_direction;
}

QString AbstractWeatherModel::windDirection(const int& degrees) const
{
    if (degrees == 0)
        return "Северный";
    else if (0 < degrees && degrees < 90)
        return "Северо-Восточный";
    else if (degrees == 90)
        return "Восточный";
    else if (90 < degrees && degrees < 180)
        return "Юго-Восточный";
    else if (degrees == 180)
        return "Южный";
    else if (180 < degrees && degrees < 270)
        return "Юго-Западный";
    else if (degrees == 270)
        return "Западный";
    else
        return "Северо-Западный";
}
