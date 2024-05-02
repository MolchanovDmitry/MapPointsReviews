#include "mappointui.h"

MapPointUi::MapPointUi(QObject* parent)
    : QObject(parent)
    , id(0)
    , title("")
    , description("")
    , latitude(0.0)
    , longitude(0.0)
    , isConfirmed(false)
    , imageUrls(QList<QString>()) {
}

MapPointUi::MapPointUi(qint64 id,
                       QString title,
                       QString description,
                       double latitude,
                       double longitude,
                       bool isConfirmed,
                       QList<QString> imageUrls,
                       QObject *parent)
    : QObject(parent)
    , id(id)
    , title(title)
    , description(description)
    , latitude(latitude)
    , longitude(longitude)
    , isConfirmed(isConfirmed)
    , imageUrls(imageUrls) {
}

qint64 MapPointUi::getId() const {
    return id;
}

QString MapPointUi::getTitle() const {
    return title;
}

QString MapPointUi::getDescription() const {
    return description;
}

double MapPointUi::getLatitude() const {
    return latitude;
}

double MapPointUi::getLongitude() const {
    return longitude;
}

bool MapPointUi::getIsConfirmed() const {
    return isConfirmed;
}

QList<QString> MapPointUi::getImageUrsl() const {
    return imageUrls;
}

