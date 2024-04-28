#include "mappointmodel.h"

MapPointModel::MapPointModel(QObject *parent) : QObject(parent)
{

}

QList<MapPoint *> MapPointModel::getMapPoints() {
    qDebug()<<"MapPointModel getMapPoints";
    return mapPoints;
}

void MapPointModel::updateMapPoints(QList<MapPoint *> mapPoints){
    qDebug()<<"MapPointModel updateMapPoints";
    this->mapPoints = mapPoints;
    emit mapPointsUpdated(this->mapPoints);
}
