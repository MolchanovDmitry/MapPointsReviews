#include "repository.h"

#include <QDebug>
#include <QSqlDatabase>
#include "repext.cpp"

Repository::Repository(QObject *parent) : QObject(parent)
{

    auto db = getDatabase();

    dataSource = new MapPointsDbDataSource(db, parent);
    dataSource->createTable();

    bool isMockDataAddedAlready = dataSource->getRowCount() != 0;
    if(!isMockDataAddedAlready){
        addMockMapPoints(dataSource);
    }

    connect(dataSource->mapPointSqlModel, &MapPointSqlModel::mapPointsFromDataUpdated,
            mapPointModel, &MapPointModel::updateMapPoints);
}

void Repository::fetchAllMapPoints()
{
    dataSource->getAll();
}

MapPointModel *Repository::getMapPointModel()
{
    return mapPointModel;
}


