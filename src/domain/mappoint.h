#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <QString>

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

#endif // MAPPOINT_H
