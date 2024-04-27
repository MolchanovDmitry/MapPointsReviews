#include "mappointui.h"

MapPointUi::MapPointUi(QObject* parent)
    : QObject(parent)
    , id(0)
    , title("")
    , description("")
    , latitude(0.0)
    , longitude(0.0)
{
}

MapPointUi::MapPointUi(qlonglong id, QString title, QString description, double latitude, double longitude, QObject *parent)
    : QObject(parent)
    , id(id)
    , title(title)
    , description(description)
    , latitude(latitude)
    , longitude(longitude)
{
}

qlonglong MapPointUi::getId() const
{
    return id;
}

QString MapPointUi::getTitle() const
{
    return title;
}

QString MapPointUi::getDescription() const
{
    return description;
}

double MapPointUi::getLatitude() const
{
    return latitude;
}

double MapPointUi::getLongitude() const
{
    return longitude;
}

