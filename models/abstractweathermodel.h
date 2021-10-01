#ifndef ABSTRACTWEATHERMODEL_H
#define ABSTRACTWEATHERMODEL_H

#include <QString>
#include <QSize>
#include <QIcon>
#include <QVariantMap>
#include <QObject>
#include <functional>
#include <QHash>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

using PointersMap = QHash<short, std::function<QString(double)>>;

namespace TEMPERATURE {
    const ushort CELSIUS      = 0x0001;
    const ushort KELVIN       = 0x0002;
    const ushort FARENHEIT    = 0x0003;

    const ushort MASK         = 0x000F;
}

namespace PRESSURE {
    const ushort MMHG         = 0x0010;
    const ushort PA           = 0x0020;
    const ushort HPA          = 0x0030;
    const ushort MBAR         = 0x0040;

    const ushort MASK         = 0x00F0;
}

namespace DISTANCE {
    const ushort KM           = 0x0100;
    const ushort METERS       = 0x0200;
    const ushort MILES        = 0x0300;

    const ushort MASK         = 0x0F00;
}

namespace WINDSPEED {
    const ushort METERSPERSEC = 0x1000;
    const ushort KMPERHOUR    = 0x2000;
    const ushort KNOT         = 0x3000;
    const ushort FTPERSEC     = 0x4000;
    const ushort MILESPERHOUR = 0x5000;

    const ushort MASK         = 0xF000;
}

class AbstractWeatherModel
{
    static ushort CONFIGURATION;
    static PointersMap pressure_functions;
    static PointersMap temperature_functions;
    static PointersMap distances_functions;
    static PointersMap windspeed_functions;
    QString windDirection(const int &degrees) const;
protected:
    QVariantMap data;
public:
    AbstractWeatherModel();
    void loadFromJson();
    void updateModel(QVariantMap &new_data);
    auto asJsonObject()                { return QJsonObject::fromVariantMap(data); }
    QString pressure() const               { return pressure_functions[PRESSURE::MASK & CONFIGURATION](data["pressure"].toDouble()); }
    QString temperature(QString key) const  { return temperature_functions[TEMPERATURE::MASK & CONFIGURATION](data[key].toDouble()); }
    QString dewPoint() const                { return temperature_functions[TEMPERATURE::MASK & CONFIGURATION](data["dew_point"].toDouble()); }
    QString visibility() const              { return distances_functions[DISTANCE::MASK & CONFIGURATION](data["visibility"].toDouble()); }
    QString uvi() const                     { return data["uvi"].toString(); }
    QString cloudness() const               { return data["cloudness"].toString() + "%"; }
    QString humidity() const                { return data["humidity"].toString() + "%"; }
    QPixmap weatherIcon() const;
    QString wind() const;
};



#endif // ABSTRACTWEATHERMODEL_H
