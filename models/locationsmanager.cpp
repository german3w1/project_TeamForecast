#include "models/locationsmanager.h"

LocationsManager::LocationsManager(QObject *parent, LocationForecast *location_view)
: QObject(parent)
{
    locations = QList<LocationModel*>(0);
    location_view_ = location_view;
}

auto LocationsManager::favourite()
{
    QList<LocationModel*> result;
    for (auto &each : locations)
        if (each->isFavourite())
            result.push_back(each);
    return result;
}

auto LocationsManager::nonFavourite()
{
    QList<LocationModel*> result;
    for (auto &each : locations)
        if (!each->isFavourite())
            result.push_back(each);
    return result;
}

void LocationsManager::updateAll()
{
    for (auto &each : locations)
        each->updateModel();
}

void LocationsManager::deleteModel(LocationModel *model)
{
    auto el = locations.takeAt(locations.indexOf(model));
    el->deleteLater();
}

