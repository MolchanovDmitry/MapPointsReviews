#include "mappointui.h"

MapPointUi::MapPointUi(QObject* parent)
    : QObject(parent)
    , id(0)
    , title("")
    , description("")
    , latitude(0.0)
    , longitude(0.0)
    , isConfirmed(false)
{
}

MapPointUi::MapPointUi(qlonglong id, QString title, QString description, double latitude, double longitude, bool isConfirmed, QObject *parent)
    : QObject(parent)
    , id(id)
    , title(title)
    , description(description)
    , latitude(latitude)
    , longitude(longitude)
    , isConfirmed(isConfirmed)
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

bool MapPointUi::getIsConfirmed() const
{
    return isConfirmed;
}

