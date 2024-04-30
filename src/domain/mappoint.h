#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <QString>
#include <QDebug>

/**
 * Бизнесовая структура точки на карте
 */
struct MapPoint {
    qlonglong id;
    QString title;
    QString description;
    double latitude;
    double longitude;
    bool isConfirmed;
    QList<QString> imageUrls;
};

static void printMapPoint(MapPoint *mapPoint, QString tag = "") {
    qDebug()<<tag<<mapPoint->title<<" "<<mapPoint->description<<" "<<mapPoint->latitude<<" "<<mapPoint->longitude<<" "<<mapPoint->isConfirmed;
}

#endif // MAPPOINT_H
