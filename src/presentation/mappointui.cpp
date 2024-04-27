#include "mappointui.h"

MapPointUi::MapPointUi(QObject* parent)
    : QObject(parent)
    , title("")
    , description("")
    , latitude(0.0)
    , longitude(0.0)
{
}

MapPointUi::MapPointUi(QString title, QString description, double latitude, double longitude, QObject *parent)
    : QObject(parent)
    , title(title)
    , description(description)
    , latitude(latitude)
    , longitude(longitude)
{
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

void MapPointUi::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        emit titleChanged();
    }
}

void MapPointUi::setDescription(const QString &description)
{
    if (this->description != description) {
        this->description = description;
        emit descriptionChanged();
    }
}

void MapPointUi::setLatitude(double latitude)
{
    if (qFuzzyCompare(this->latitude, latitude) == false) {
        this->latitude = latitude;
        emit latitudeChanged();
    }
}

void MapPointUi::setLongitude(double longitude)
{
    if (qFuzzyCompare(this->longitude, longitude) == false) {
        this->longitude = longitude;
        emit longitudeChanged();
    }
}
