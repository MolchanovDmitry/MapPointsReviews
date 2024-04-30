#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include "mappoint.h"
#include "mappointmodel.h"
#include "commentbyidmodel.h"

class Repository : public QObject
{
    Q_OBJECT
public:
    Repository(QObject *parent = nullptr) : QObject(parent) {};

    virtual void fetchAllMapPoints() = 0;

    virtual void addMapPoint(MapPoint mapPoint) = 0;

    virtual void addComment(int mapPointId, QString comment) = 0;

    virtual void fetchCommentsBy(int mapPointId) = 0;

    virtual MapPointModel *getMapPointModel() = 0;

    virtual CommentsByIdModel *getCommentsByIdModel() = 0;

};

#endif // REPOSITORY_H
