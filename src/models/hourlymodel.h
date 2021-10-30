#ifndef HOURLYMODEL_H
#define HOURLYMODEL_H

#include "models/abstractweathermodel.h"

class HourlyModel : public AbstractWeatherModel
{
public:
    HourlyModel();
    void updateModel(const QVariantMap &new_data, const QDateTime &today, const int &offset);
    QString day() const;
    QDateTime today() const { return data["today"].toDateTime(); }
    QString time() const   { return data["date_time"].toDateTime().time().toString("hh:mm"); };
};

#endif // HOURLYMODEL_H
