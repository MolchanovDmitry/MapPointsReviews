#include "repository.h"

#include <QDebug>
#include <QSqlDatabase>
#include "repext.cpp"

Repository::Repository(
        MapPointsDbDataSource *mapPointsDataSource,
        CommentsDataSource *commentsDataSource,
        QObject *parent)
    : QObject(parent),
     commentsDataSource(commentsDataSource),
     mapPointsDataSource(mapPointsDataSource)
{
    mapPointsDataSource->createTables();
    commentsDataSource->createTable();

    bool isMockDataAddedAlready = mapPointsDataSource->getRowCount() != 0;
    if(!isMockDataAddedAlready){
        addMockMapPoints(mapPointsDataSource);
    }

    connect(mapPointsDataSource->mapPointSqlModel, &MapPointSqlModel::mapPointsFromDataUpdated,
            mapPointModel, &MapPointModel::updateMapPoints);
    connect(commentsDataSource->getTableModel(), &QSqlTableModel::modelReset,
            []{
            qDebug()<<"model reset";
    });
}

void Repository::fetchAllMapPoints()
{
    mapPointsDataSource->getAll();
}

void Repository::addMapPoint(MapPoint mapPoint)
{
    mapPointsDataSource->addRow(mapPoint);
}

void Repository::addComment(int mapPointId, QString comment){
    commentsDataSource->addComment(mapPointId, comment);
}

void Repository::fetchCommentsBy(int mapPointId){
    commentsDataSource->fetchCommentsBy(mapPointId);
}

MapPointModel *Repository::getMapPointModel()
{
    return mapPointModel;
}


