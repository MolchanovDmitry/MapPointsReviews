#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "mappointsdbdatasource.h"
#include "commentsdatasource.h"
#include "../domain/mappointmodel.h"
#include "../domain/commentbyidmodel.h"


class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(
            MapPointsDbDataSource *mapPointsDbDataSource,
            CommentsDataSource *commentsDataSource,
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

    MapPointModel *mapPointModel = new MapPointModel();

    CommentsByIdModel *commentsByIdModel = new CommentsByIdModel();

    void addFakeData();

};

#endif // REPOSITORY_H
