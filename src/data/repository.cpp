#include "repository.h"

#include <QDebug>
#include <QMutexLocker>
#include <QSqlDatabase>
#include "repext.cpp"

Repository::Repository(
        MapPointsDbDataSource *mapPointsDataSource,
        CommentsDataSource *commentsDataSource,
        NotificationSender *notificationSender,
        StringProvider *stringProvider,
        QObject *parent)
    : QObject(parent),
     commentsDataSource(commentsDataSource),
     mapPointsDataSource(mapPointsDataSource),
     notificationSender(notificationSender),
     stringProvider(stringProvider)
{
    QMutexLocker locker(&mapPointsDataSourceMutex);
    QMutexLocker locker2(&commentsDataSourceMutex);
    mapPointsDataSource->createTables();
    commentsDataSource->createTable();

    bool isMockDataAddedAlready = mapPointsDataSource->getRowCount() != 0;
    if(!isMockDataAddedAlready){
        addMockMapPoints(mapPointsDataSource);
    }
    locker.unlock();
    locker2.unlock();

    connect(mapPointsDataSource->mapPointSqlModel, &MapPointTableModel::mapPointsFromDataUpdated,
            mapPointModel, &MapPointModel::updateMapPoints);
    connect(commentsDataSource->getTableModel(), &CommentsTableModel::commentsFetched,
            commentsByIdModel, &CommentsByIdModel::updateComments);
}

void Repository::fetchAllMapPoints()
{
    QMutexLocker locker(&mapPointsDataSourceMutex);
    mapPointsDataSource->getAll();
}

void Repository::addMapPoint(MapPoint mapPoint)
{
    QMutexLocker locker(&mapPointsDataSourceMutex);
    auto isPointAdded = mapPointsDataSource->addRow(mapPoint);
    if(isPointAdded) {
        auto notificationBody = stringProvider->provide(AppString::PointSentNotification)
                .arg(mapPoint.title);
        notificationSender->notify(notificationBody);
    }
}

void Repository::addComment(int mapPointId, QString comment){
    QMutexLocker locker(&commentsDataSourceMutex);
    commentsDataSource->addComment(mapPointId, comment);
}

void Repository::fetchCommentsBy(int mapPointId){
    QMutexLocker locker(&commentsDataSourceMutex);
    commentsDataSource->fetchCommentsBy(mapPointId);
}

MapPointModel *Repository::getMapPointModel()
{
    return mapPointModel;
}

CommentsByIdModel *Repository::getCommentsByIdModel(){
    return commentsByIdModel;
}


