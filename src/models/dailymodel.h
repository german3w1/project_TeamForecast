#ifndef DAILYMODEL_H
#define DAILYMODEL_H

#include "src/models/abstractweathermodel.h"

class DailyModel : public AbstractWeatherModel {
public:
    DailyModel();
    QString visibility() = delete;
    void updateModel(const QVariantMap& new_data, const int& offset);
    QString date() const { return data["date"].toDate().toString("dd.MM"); }
    QString dayOfWeek() const { return QLocale::system().dayName(data["date"].toDate().dayOfWeek(), QLocale::ShortFormat); }
};

#endif // DAILYMODEL_H
