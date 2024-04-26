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

    MapPointModel* mapPointModel = new MapPointModel();

    void fetchAllMapPoints();

private:
    MapPointsDbDataSource* dataSource;

    void addFakeData();

};

#endif // REPOSITORY_H
