#include "mapviewmodel.h"


MapViewModel::MapViewModel(
        FetchAllMapPointsUseCase *fetchAppMapPointsUseCase,
        GetMapPointModelUseCase *getMapPointModelUseCase,
        QObject *parent)
    : QObject(parent)
{
    connect(getMapPointModelUseCase->run(), &MapPointModel::mapPointsUpdated,
            this, &MapViewModel::mapMapPointAndUpdate);

    fetchAppMapPointsUseCase->run();
}

void MapViewModel::mapMapPointAndUpdate(QList<MapPoint*> mapPoints)
{
    QList<MapPointUi*> uiMapPoints = QList<MapPointUi*>();
    foreach(MapPoint *mapPoint, mapPoints){
        uiMapPoints << new MapPointUi(mapPoint->id,
                                      mapPoint->title,
                                      mapPoint->description,
                                      mapPoint->latitude,
                                      mapPoint->longitude,
                                      mapPoint->isConfirmed,
                                      mapPoint->imageUrls);
    }
    mapPointsUiModel->updateMapPoints(uiMapPoints);
}

MapPointsUiModel* MapViewModel::getMapPointsUiModel()
{
    return mapPointsUiModel;
}
