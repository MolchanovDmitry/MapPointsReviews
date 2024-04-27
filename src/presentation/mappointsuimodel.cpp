#include "mappointsuimodel.h"

MapPointsUiModel::MapPointsUiModel(QObject *parent) : QAbstractListModel(parent) {}


int MapPointsUiModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return mapPoints.count();
}

QVariant MapPointsUiModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    MapPointUi *point = mapPoints[index.row()];
    switch (role) {
    case TitleRole:
        return QVariant(point->getTitle());
    case DescriptionRole:
        return QVariant(point->getDescription());
    case LatitudeRole:
        return QVariant(point->getLatitude());
    case LongitudeRole:
        return QVariant(point->getLongitude());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MapPointsUiModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[DescriptionRole] = "description";
    roles[LatitudeRole] = "latitude";
    roles[LongitudeRole] = "longitude";
    return roles;
}

void MapPointsUiModel::updateMapPoints(QList<MapPoint *> mapPoints)
{
    qDebug()<<"MapPointsUiModel updateMapPoints";
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    this->mapPoints.clear();

    QList<MapPointUi*> uiMapPoints = QList<MapPointUi*>();
    foreach(MapPoint *mapPoint, mapPoints){
        uiMapPoints << new MapPointUi(mapPoint->title, mapPoint->description, mapPoint->latitude, mapPoint->longitude);
    }
    this->mapPoints << uiMapPoints;

    endInsertRows();
}
