#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "mappointsdbdatasource.h"

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);

    const QList<MapPoint> getAllMapPoints();

private:
    MapPointsDbDataSource *dataSource;

    void addFakeData();
};

#endif // REPOSITORY_H
