#ifndef ADDMAPPOINTHANDLER_H
#define ADDMAPPOINTHANDLER_H

#include <QObject>
#include <QDebug>
#include "../../domain/mappoint.h"

/**
 * Обработчик намерения добавить новую точку на карте
 */
class AddMapPointHandler : public QObject {
    Q_OBJECT
  public:
    explicit AddMapPointHandler(QObject *parent = nullptr);

  public slots:

    /** Слот, который вызывается из UI части */
    void onMapPointAddRequest(
        const QString title,
        const QString description,
        const QVariant imageUrls,
        const double latitude,
        const double longitude);

  signals:

    /** Уже преобразованный сигнал с готовым [MapPoint], который вызывается из слота [onMapPointAddRequest] */
    void onMapPointPretentderFetched(MapPoint mapPoint);
};

#endif // ADDMAPPOINTHANDLER_H
