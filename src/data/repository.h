#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QMutex>

#include "mappointsdbdatasource.h"
#include "commentsdatasource.h"
#include "notificationsender.h"
#include "../domain/mappointmodel.h"
#include "../domain/commentbyidmodel.h"
#include "../stringprovider.h"


class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(
            MapPointsDbDataSource *mapPointsDbDataSource,
            CommentsDataSource *commentsDataSource,
            NotificationSender *notificationSender,
            StringProvider *stringProvider,
            QObject *parent = nullptr
            );

    void fetchAllMapPoints();

    void addMapPoint(MapPoint mapPoint);

    void addComment(int mapPointId, QString comment);

    void fetchCommentsBy(int mapPointId);

    MapPointModel *getMapPointModel();

    CommentsByIdModel *getCommentsByIdModel();

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

#endif // REPOSITORY_H
