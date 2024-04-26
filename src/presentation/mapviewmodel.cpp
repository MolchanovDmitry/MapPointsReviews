#include "mapviewmodel.h"

MapViewModel::MapViewModel(Repository *repository, QObject *parent)
    : QObject(parent),
      mapPointsUiModel(MapPointsUiModel()){
    this->repository = repository;

    connect(this->repository->mapPointModel,&MapPointModel::mapPointsUpdated,
            &this->mapPointsUiModel, &MapPointsUiModel::updateMapPoints);

    repository->fetchAllMapPoints();
}

MapPointsUiModel &MapViewModel::getMapPointsUiModel()
{
    return mapPointsUiModel;
}
