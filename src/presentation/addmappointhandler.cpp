#include "addmappointhandler.h"

AddMapPointHandler::AddMapPointHandler(QObject *parent) : QObject(parent)
{

}

void AddMapPointHandler::onMapPointAddRequest(const QString title, const QString description, const QVariant imageUrls, const double latitude, const double longitude){
    MapPoint mapPoint;
    mapPoint.title = title;
    mapPoint.description = description;
    mapPoint.imageUrls = imageUrls.value<QList<QString>>();
    mapPoint.latitude = latitude;
    mapPoint.longitude = longitude;
    mapPoint.isConfirmed = false;

    emit onMapPointPretentderFetched(mapPoint);
}
