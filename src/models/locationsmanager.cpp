#include "src/models/locationsmanager.h"

LocationsManager* LocationsManager::instance_ = nullptr;

LocationsManager* LocationsManager::getInstance(QObject* parent, LocationForecast* location_view)
{
    if (instance_ == nullptr)
        instance_ = new LocationsManager(parent, location_view);
    return instance_;
}

LocationsManager::LocationsManager(QObject* parent,
    LocationForecast* location_view)
    : QObject(parent)
{
    locations = QList<LocationModel*>(0);
    location_view_ = location_view;

    update_timer_ = new QTimer(this);
    connect(update_timer_, &QTimer::timeout,
        this, &LocationsManager::updateAll);
}

void LocationsManager::setUpdateInterval(int msec)
{
    if (msec)
        update_timer_->start(msec);
    else
        update_timer_->stop();
}

void LocationsManager::add(QString lat, QString lon, QString label)
{
    auto new_model = new LocationModel(lat, lon, label);
    new_model->updateModel();
    locations.push_back(new_model);
    emit contentChanged();
}

auto LocationsManager::favourite()
{
    QList<LocationModel*> result;
    for (auto& each : locations)
        if (each->isFavourite())
            result.push_back(each);
    return result;
}

auto LocationsManager::nonFavourite()
{
    QList<LocationModel*> result;
    for (auto& each : locations)
        if (!each->isFavourite())
            result.push_back(each);
    return result;
}

LocationsManager::~LocationsManager()
{
    instance_ = nullptr;
}

void LocationsManager::updateAll()
{
    for (auto& each : locations)
        each->updateModel();
}

void LocationsManager::deleteModel(LocationModel* model)
{
    auto el = locations.takeAt(locations.indexOf(model));
    el->deleteLater();
}
