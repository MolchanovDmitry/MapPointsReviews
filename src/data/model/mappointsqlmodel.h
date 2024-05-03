#ifndef MAPPOINTSQLMODEL_H
#define MAPPOINTSQLMODEL_H

#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlTableModel>
#include "../../domain/model/mappoint.h"

/**
 * Sql модель всех точек на карте.
 */
class MapPointTableModel : public QSqlTableModel {
    Q_OBJECT

  public:
    explicit MapPointTableModel(QObject *parent = nullptr);

  public slots:
    /**
     *  При изменении произойдет мапинг данных в бизнес модель
     *  с последующим вызовом [mapPointsFromDataUpdated]
     */
    void onDataChanged();

  signals:

    /** Уведомляем подпищиков об изменении модели в формате бизнес модели */
    void mapPointsFromDataUpdated(QList<MapPoint*> mapPoints);
};

#endif // MAPPOINTSQLMODEL_H
