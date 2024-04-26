#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <QString>
#include <QDebug>

/**
 * Бизнесовая структура точки на карте
 */
struct MapPoint
{
    qlonglong id;
    QString title;
    QString description;
    double latitude;
    double longitude;
};

static void printMapPoint(MapPoint mapPoint, QString tag = ""){
    qDebug()<<tag<<mapPoint.title<<" "<<mapPoint.description<<" "<<mapPoint.latitude<<" "<<mapPoint.longitude;
}

#endif // MAPPOINT_H
