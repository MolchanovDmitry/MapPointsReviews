#include "repositoryimpl.h"

#include <QDebug>
#include <QMutexLocker>
#include <QSqlDatabase>
#include "repext.cpp"

RepositoryImpl::RepositoryImpl(
    MapPointsDbDataSource *mapPointsDataSource,
    ReviewsDataSource *reviewsDataSource,
    NotificationSender *notificationSender,
    StringProvider *stringProvider,
    QObject *parent)
    : Repository(parent),
      reviewsDataSource(reviewsDataSource),
      mapPointsDataSource(mapPointsDataSource),
      notificationSender(notificationSender),
      stringProvider(stringProvider) {

    QMutexLocker locker(&mapPointsDataSourceMutex);
    QMutexLocker locker2(&reviewsDataSourceMutex);
    mapPointsDataSource->createTable();
    reviewsDataSource->createTable();

    bool isMockDataAddedAlready = mapPointsDataSource->getPointsCount() != 0;
    if(!isMockDataAddedAlready) {
        addMockMapPoints(mapPointsDataSource);
    }
    locker.unlock();
    locker2.unlock();

    connect(mapPointsDataSource->getMapPointTableModel(), &MapPointTableModel::mapPointsFromDataUpdated,
            mapPointModel, &MapPointModel::updateMapPoints);
    connect(reviewsDataSource->getTableModel(), &ReviewsTableModel::reviewsFetched,
            reviewsByIdModel, &ReviewsByIdModel::updateReviews);
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

void RepositoryImpl::addReview(int mapPointId, Review review) {
    QMutexLocker locker(&reviewsDataSourceMutex);
    reviewsDataSource->addReview(mapPointId, review);
}

void RepositoryImpl::fetchReviewsBy(int mapPointId) {
    QMutexLocker locker(&reviewsDataSourceMutex);
    reviewsDataSource->fetchReviewsBy(mapPointId);
}

MapPointModel *RepositoryImpl::getMapPointModel() {
    return mapPointModel;
}

ReviewsByIdModel *RepositoryImpl::getReviewsByIdModel() {
    return reviewsByIdModel;
}


