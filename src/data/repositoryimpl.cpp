#include "repositoryimpl.h"

#include <QDebug>
#include <QMutexLocker>
#include <QSqlDatabase>
#include "repext.cpp"

RepositoryImpl::RepositoryImpl(
    MapPointsDbDataSource *mapPointsDataSource,
    CommentsDataSource *commentsDataSource,
    NotificationSender *notificationSender,
    StringProvider *stringProvider,
    QObject *parent)
    : Repository(parent),
      commentsDataSource(commentsDataSource),
      mapPointsDataSource(mapPointsDataSource),
      notificationSender(notificationSender),
      stringProvider(stringProvider) {

    QMutexLocker locker(&mapPointsDataSourceMutex);
    QMutexLocker locker2(&commentsDataSourceMutex);
    mapPointsDataSource->createTable();
    commentsDataSource->createTable();

    bool isMockDataAddedAlready = mapPointsDataSource->getPointsCount() != 0;
    if(!isMockDataAddedAlready) {
        addMockMapPoints(mapPointsDataSource);
    }
    locker.unlock();
    locker2.unlock();

    connect(mapPointsDataSource->getMapPointTableModel(), &MapPointTableModel::mapPointsFromDataUpdated,
            mapPointModel, &MapPointModel::updateMapPoints);
    connect(commentsDataSource->getTableModel(), &CommentsTableModel::commentsFetched,
            commentsByIdModel, &CommentsByIdModel::updateComments);
}

void RepositoryImpl::fetchAllMapPoints() {
    QMutexLocker locker(&mapPointsDataSourceMutex);
    mapPointsDataSource->fetchAllMapPoints();
}

void RepositoryImpl::addMapPoint(MapPoint mapPoint) {
    QMutexLocker locker(&mapPointsDataSourceMutex);
    auto isPointAdded = mapPointsDataSource->addMapPoin(mapPoint);
    if(isPointAdded) {
        auto notificationBody = stringProvider->provide(AppString::PointSentNotification)
                                .arg(mapPoint.title);
        notificationSender->notify(notificationBody);
    }
}

void RepositoryImpl::addComment(int mapPointId, QString comment) {
    QMutexLocker locker(&commentsDataSourceMutex);
    commentsDataSource->addComment(mapPointId, comment);
}

void RepositoryImpl::fetchCommentsBy(int mapPointId) {
    QMutexLocker locker(&commentsDataSourceMutex);
    commentsDataSource->fetchCommentsBy(mapPointId);
}

MapPointModel *RepositoryImpl::getMapPointModel() {
    return mapPointModel;
}

CommentsByIdModel *RepositoryImpl::getCommentsByIdModel() {
    return commentsByIdModel;
}


