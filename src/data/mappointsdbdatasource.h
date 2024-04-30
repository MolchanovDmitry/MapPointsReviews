#ifndef MAPPOINTSDBDATASOURCE_H
#define MAPPOINTSDBDATASOURCE_H

#include <QObject>
#include <QList>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "mappointsqlmodel.h"
#include "../domain/mappoint.h"

/**
 * Источник данных точек на карте
 */
class MapPointsDbDataSource : public QObject {
    Q_OBJECT
  public:
    explicit MapPointsDbDataSource(QSqlDatabase db, QObject *parent = nullptr);

    /** Создать таблицы для хранения точек (при необходимости) */
    void createTable();

    /** Добавить точку */
    bool addMapPoin(MapPoint mapPoint);

    /** Добавить точки */
    bool addMapPoints(QList<MapPoint*> *mapPoints);

    /** Получить количество строк */
    int getPointsCount();

    /** Получить все точки */
    void fetchAllMapPoints();

    /** Получить модель точек на карте. */
    MapPointTableModel* getMapPointTableModel();

  private:

    QSqlDatabase db;

    MapPointTableModel *mapPointSqlModel = new MapPointTableModel(this);

    void createMapPointTable();

    void createCommentsTable();

};

#endif // MAPPOINTSDBDATASOURCE_H
