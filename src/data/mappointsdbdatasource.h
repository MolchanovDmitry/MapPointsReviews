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

    void createTable();

    void addRow(const MapPoint mapPoint);

    void addRows(const QList<MapPoint> mapPoints);

    int getRowCount();

    void getAll();



private:
    QSqlDatabase db;

};

#endif // MAPPOINTSDBDATASOURCE_H
