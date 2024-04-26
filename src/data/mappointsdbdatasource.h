#ifndef MAPPOINTSDBDATASOURCE_H
#define MAPPOINTSDBDATASOURCE_H

#include <QObject>
#include <QList>
#include <QSqlDatabase>
#include "../domain/mappoint.h"

class MapPointsDbDataSource : public QObject
{
    Q_OBJECT
public:
    explicit MapPointsDbDataSource(QSqlDatabase db, QObject *parent = nullptr);

    void createTable();

    void addRow(const MapPoint mapPoint);

    void addRows(const QList<MapPoint> mapPoints);

    int getRowCount();

    const QList<MapPoint> getAll();

private:
    QSqlDatabase db;

};

#endif // MAPPOINTSDBDATASOURCE_H
