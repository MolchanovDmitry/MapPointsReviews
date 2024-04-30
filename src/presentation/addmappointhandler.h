#ifndef ADDMAPPOINTHANDLER_H
#define ADDMAPPOINTHANDLER_H

#include <QObject>
#include <QDebug>
#include "../domain/mappoint.h"

class AddMapPointHandler : public QObject {
    Q_OBJECT
  public:
    explicit AddMapPointHandler(QObject *parent = nullptr);

  public slots:
    void onMapPointAddRequest(
        const QString title,
        const QString description,
        const QVariant imageUrls,
        const double latitude,
        const double longitude);

  signals:
    void onMapPointPretentderFetched(MapPoint mapPoint);
};

#endif // ADDMAPPOINTHANDLER_H
