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

    MapPointTableModel *mapPointSqlModel = new MapPointTableModel(this); //TODO

    void createTables();

    bool addRow(MapPoint mapPoint);

    bool addRows(QList<MapPoint*> *mapPoints);

    int getRowCount();

    void getAll();



private:
    QSqlDatabase db;

    void createMapPointTable();

    void createCommentsTable();

};

#endif // MAPPOINTSDBDATASOURCE_H
