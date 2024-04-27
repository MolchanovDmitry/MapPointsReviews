#include "repository.h"

#include <QDebug>
#include <QSqlDatabase>
#include "repext.cpp"

Repository::Repository(QObject *parent) : QObject(parent)
{

    auto db = getDatabase();

    this->dataSource = new MapPointsDbDataSource(db, parent);
    this->dataSource->createTable();

    bool isMockDataAddedAlready = dataSource->getRowCount() != 0;
    if(!isMockDataAddedAlready){
        addMockMapPoints(this->dataSource);
    }

    connect(this->dataSource->mapPointSqlModel,&MapPointSqlModel::mapPointsFromDataUpdated,
            this->mapPointModel, &MapPointModel::updateMapPoints);
}

void Repository::fetchAllMapPoints()
{
    dataSource->getAll();
}


