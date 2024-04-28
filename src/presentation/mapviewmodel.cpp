#include "mapviewmodel.h"


MapViewModel::MapViewModel(
        FetchAllMapPointsUseCase *fetchAppMapPointsUseCase,
        GetMapPointModelUseCase *getMapPointModelUseCase,
        AddMapPointUseCase *addMapPointUseCase,
        QObject *parent)
    : QObject(parent)
    , addMapPointUseCase(addMapPointUseCase)
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

void MapViewModel::onMapPointPretentderFetched(MapPoint mapPoint){
    printMapPoint(&mapPoint, "onMapPointPretentderFetched");
    addMapPointUseCase->run(mapPoint);
}
