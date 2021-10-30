#ifndef LOCATIONSMANAGER_H
#define LOCATIONSMANAGER_H
#include <src/models/locationmodel.h>
#include <src/views/locationforecast.h>
#include <QObject>
#include <QTimer>

class LocationsManager : public QObject
{
    Q_OBJECT
private:
    static LocationsManager *instance_;
    QList<LocationModel*> locations;
    LocationForecast* location_view_;
    QTimer *update_timer_;
    LocationsManager(QObject *parent, LocationForecast *location_view);
public:
    static LocationsManager* getInstance(QObject *parent = nullptr, LocationForecast *location_view = nullptr);
    void setUpdateInterval(int msec);
    void add(QString lat, QString lon, QString label);
    auto all() const                                       { return locations; }
    auto favourite();
    auto nonFavourite();
    auto location_view() { return location_view_; }
    auto count() { return locations.size(); }
    ~LocationsManager();
public slots:
    void updateAll();
    void deleteModel(LocationModel *model);
signals:
    void contentChanged();
};

#endif // LOCATIONSMANAGER_H
