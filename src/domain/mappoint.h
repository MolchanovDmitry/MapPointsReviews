#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <QString>
#include <QDebug>

/**
 * Бизнесовая структура точки на карте
 */
struct MapPoint {
    /** ID точки на карте. */
    qlonglong id;

    /** Название точки на карте. */
    QString title;

    /** Описание точки на карте. */
    QString description;

    /** Географическая широта точки на карте. */
    double latitude;

    /** Географическая долгота точки на карте. */
    double longitude;

    /** Подтверждена ли точка модератором. */
    bool isConfirmed;

    /** Список ссылок изображений точки на карте. */
    QList<QString> imageUrls;
};

static void printMapPoint(MapPoint *mapPoint, QString tag = "") {
    qDebug()<<tag<<mapPoint->title<<" "<<mapPoint->description<<" "<<mapPoint->latitude<<" "<<mapPoint->longitude<<" "<<mapPoint->isConfirmed;
}

#endif // MAPPOINT_H
