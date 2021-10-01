#ifndef LOCATIONSMANAGER_H
#define LOCATIONSMANAGER_H
#include <models/locationmodel.h>
#include <views/locationforecast.h>
#include <QObject>

class LocationsManager : public QObject
{
    Q_OBJECT
private:
    QList<LocationModel*> locations;
    LocationForecast* location_view_;
public:
    LocationsManager(QObject *parent, LocationForecast *location_view);
    void add(QString lat, QString lon, QString label) {
        locations.push_back(new LocationModel(lat, lon, label)); emit contentChanged(); }
    auto all() const                                       { return locations; }
    auto favourite();
    auto nonFavourite();
    auto location_view() { return location_view_; }
    auto count() { return locations.size() + 1; }
public slots:
    void updateAll();
    void deleteModel(LocationModel *model);
signals:
    void contentChanged();
};

#endif // LOCATIONSMANAGER_H
