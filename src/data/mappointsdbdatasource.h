#ifndef MAPPOINTSDBDATASOURCE_H
#define MAPPOINTSDBDATASOURCE_H

#include <QObject>
#include <QList>
#include <QSqlDatabase>

#include "mappointsqlmodel.h"
#include "../domain/mappoint.h"

class MapPointsDbDataSource : public QObject
{
    Q_OBJECT
public:
    explicit MapPointsDbDataSource(QSqlDatabase db, QObject *parent = nullptr);

    MapPointSqlModel *mapPointSqlModel = new MapPointSqlModel(parent());

    void createTables();

    void addRow(const MapPoint mapPoint);

    void addRows(QList<MapPoint*> *mapPoints);

    int getRowCount();

    void getAll();



private:
    QSqlDatabase db;

    void createMapPointTable();

    void createCommentsTable();

};

#endif // MAPPOINTSDBDATASOURCE_H
