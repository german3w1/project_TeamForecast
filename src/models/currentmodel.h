#ifndef CURRENTMODEL_H
#define CURRENTMODEL_H

#include "src/models/abstractweathermodel.h"

class CurrentModel : public AbstractWeatherModel {
public:
    CurrentModel();
    void updateModel(QVariantMap& new_data, const int& offset);
    QString time() const { return data["time"].toTime().toString("hh:mm"); };
};

#endif // CURRENTMODEL_H
