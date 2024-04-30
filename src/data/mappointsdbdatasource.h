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

    MapPointTableModel *mapPointSqlModel = new MapPointTableModel(this); //TODO

    /** Создать таблицы для хранения точек (при необходимости) */
    void createTables();

    /** Добавить точку */
    bool addRow(MapPoint mapPoint);

    /** Добавить точки */
    bool addRows(QList<MapPoint*> *mapPoints);

    /** Получить количество строк */
    int getRowCount();

    /** Получить все точки */
    void getAll();



  private:
    QSqlDatabase db;

    void createMapPointTable();

    void createCommentsTable();

};

#endif // MAPPOINTSDBDATASOURCE_H
