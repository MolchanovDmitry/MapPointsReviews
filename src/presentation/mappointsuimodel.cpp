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
    case IdRole:
        return QVariant(point->getId());
    case TitleRole:
        return QVariant(point->getTitle());
    case DescriptionRole:
        return QVariant(point->getDescription());
    case LatitudeRole:
        return QVariant(point->getLatitude());
    case LongitudeRole:
        return QVariant(point->getLongitude());
    case IsConfirmedRole:
        return QVariant(point->getIsConfirmed());
    case ImageUrls:
        return QVariant(point->getImageUrsl());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MapPointsUiModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "title";
    roles[DescriptionRole] = "description";
    roles[LatitudeRole] = "latitude";
    roles[LongitudeRole] = "longitude";
    roles[IsConfirmedRole] = "isConfirmed";
    roles[ImageUrls] = "imageUrls";
    return roles;
}

void MapPointsUiModel::updateMapPoints(QList<MapPointUi *> uiMapPoints)
{
    qDebug() << "MapPointsUiModel::updateMapPoints count: " << uiMapPoints.count();

    if (!mapPoints.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, mapPoints.count() - 1);
        qDeleteAll(mapPoints);
        mapPoints.clear();
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), 0, uiMapPoints.count() - 1);
    mapPoints = uiMapPoints;
    endInsertRows();
}
