#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "mappointsdbdatasource.h"
#include "../domain/mappointmodel.h"

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);

    MapPointModel* getAllMapPoints();

private:
    MapPointsDbDataSource* dataSource;

    MapPointModel* mapPointModel = new MapPointModel();

    void addFakeData();

};

#endif // REPOSITORY_H
