#ifndef MAPPOINTSDBDATASOURCE_H
#define MAPPOINTSDBDATASOURCE_H

#include <QObject>
#include <QList>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "mappointsqlmodel.h"
#include "../domain/mappoint.h"

class MapPointsDbDataSource : public QObject
{
    Q_OBJECT
public:
    explicit MapPointsDbDataSource(QSqlDatabase db, QObject *parent = nullptr);

    MapPointSqlModel *mapPointSqlModel = new MapPointSqlModel(this);

    void createTables();

    void addRow(MapPoint mapPoint);

    void addRows(QList<MapPoint*> *mapPoints);

    int getRowCount();

    void getAll();



private:
    QSqlDatabase db;

    void createMapPointTable();

    void createCommentsTable();

};

#endif // MAPPOINTSDBDATASOURCE_H
