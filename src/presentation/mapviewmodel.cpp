#include "mapviewmodel.h"


MapViewModel::MapViewModel(Repository *repository, QObject *parent)
    : QObject(parent) {
    this->repository = repository;

    connect(this->repository->mapPointModel, &MapPointModel::mapPointsUpdated, this, &MapViewModel::mapMapPointAndUpdate);

    repository->fetchAllMapPoints();
}

void MapViewModel::mapMapPointAndUpdate(QList<MapPoint*> mapPoints)
{
    QList<MapPointUi*> uiMapPoints = QList<MapPointUi*>();
    foreach(MapPoint *mapPoint, mapPoints){
        uiMapPoints << new MapPointUi(mapPoint->id, mapPoint->title, mapPoint->description, mapPoint->latitude, mapPoint->longitude);
    }
    mapPointsUiModel->updateMapPoints(uiMapPoints);
}

MapPointsUiModel* MapViewModel::getMapPointsUiModel()
{
    return mapPointsUiModel;
}
