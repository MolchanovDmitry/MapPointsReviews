#ifndef MAPPOINTSQLMODEL_H
#define MAPPOINTSQLMODEL_H

#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlRecord>
#include "../domain/mappoint.h"

class MapPointSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit MapPointSqlModel(QObject *parent = nullptr);

signals:
    void mapPointsFromDataUpdated(QList<MapPoint*> mapPoints);

public slots:
    void onDataChanged() {

        qDebug()<<"MapPointSqlModel onDataChanged";
        QList<MapPoint*> mapPoints = QList<MapPoint*>();

        for(int i = 0; i < rowCount(); i++){
           QSqlRecord record = this->record(i);
           QString title = record.value("title").toString();
           QString description = record.value("description").toString();

           MapPoint* mapPoint = new MapPoint();
           mapPoint->title = record.value("title").toString();
           mapPoint->description = record.value("description").toString();
           mapPoint->latitude = record.value("latitude").toDouble();
           mapPoint->longitude = record.value("longitude").toDouble();
           printMapPoint(mapPoint, "отлов в onDataChanged");
           mapPoints.append(mapPoint);
        }
        emit mapPointsFromDataUpdated(mapPoints);
    }
};

#endif // MAPPOINTSQLMODEL_H
