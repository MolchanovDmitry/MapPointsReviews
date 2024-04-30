#include "mappointsqlmodel.h"

MapPointTableModel::MapPointTableModel(QObject *parent): QSqlTableModel(parent) {
    connect(this, &QAbstractItemModel::modelReset, this, &MapPointTableModel::onDataChanged);
}

void MapPointTableModel::onDataChanged() {

    qDebug()<<"MapPointSqlModel onDataChanged rowCount = "<<rowCount();
    QList<MapPoint*> mapPoints = QList<MapPoint*>();

    for(int i = 0; i < rowCount(); i++) {
        QSqlRecord record = this->record(i);

        MapPoint* mapPoint = new MapPoint();
        mapPoint->id = record.value("id").toLongLong();
        mapPoint->title = record.value("title").toString();
        mapPoint->description = record.value("description").toString();
        mapPoint->latitude = record.value("latitude").toDouble();
        mapPoint->longitude = record.value("longitude").toDouble();
        mapPoint->isConfirmed = record.value("confirm_status").toString() == "1";
        mapPoint->imageUrls = record.value("image_urls").toString().split("|");

        //printMapPoint(mapPoint, "отлов в onDataChanged");
        mapPoints.append(mapPoint);
    }
    emit mapPointsFromDataUpdated(mapPoints);
}
