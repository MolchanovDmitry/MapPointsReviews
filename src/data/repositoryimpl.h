#ifndef REPOSITORYIMPL_H
#define REPOSITORYIMPL_H

#include <QObject>
#include <QMutex>

#include "mappointsdbdatasource.h"
#include "commentsdatasource.h"
#include "notificationsender.h"
#include "../domain/repository.h"
#include "../stringprovider.h"


class RepositoryImpl : public Repository {
    Q_OBJECT
  public:
    explicit RepositoryImpl(
        MapPointsDbDataSource *mapPointsDbDataSource,
        CommentsDataSource *commentsDataSource,
        NotificationSender *notificationSender,
        StringProvider *stringProvider,
        QObject *parent = nullptr
    );

    void fetchAllMapPoints() override;

    void addMapPoint(MapPoint mapPoint) override;

    void addComment(int mapPointId, QString comment) override;

    void fetchCommentsBy(int mapPointId) override;

    MapPointModel *getMapPointModel() override;

    CommentsByIdModel *getCommentsByIdModel() override;

  private:

    CommentsDataSource *commentsDataSource;

    MapPointsDbDataSource *mapPointsDataSource;

    NotificationSender *notificationSender;

    StringProvider *stringProvider;

    MapPointModel *mapPointModel = new MapPointModel();

    CommentsByIdModel *commentsByIdModel = new CommentsByIdModel();

    QMutex commentsDataSourceMutex;

    QMutex mapPointsDataSourceMutex;

    void addFakeData();

};

#endif // REPOSITORYIMPL_H
